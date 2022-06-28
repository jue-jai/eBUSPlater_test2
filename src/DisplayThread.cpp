// *****************************************************************************
//
//     Copyright (c) 2007, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************

#include "eBUSPlayerShared.h"
#include "DisplayThread.h"
#include "ImageSaving.h"
#include "ImageFiltering.h"
#include "PvResult.h"
#include "PvString.h"
#include "PvBufferWriter.h"

#include <limits>
#include <assert.h>
#include <memory>

#include "compressed_buffer_bpp8.hpp"
#include "compressed_buffer_bpp8d.hpp"

#ifdef _AFXDLL
IMPLEMENT_DYNAMIC(DisplayThread, CObject)
#endif // _AFXDLL

///
/// \brief Constructor
///

DisplayThread::DisplayThread(
	IPvDisplayAdapter* aDisplay, ImageFiltering* aImageFiltering,
	ImageSaving* aImageSaving, LogBuffer* aLogBuffer)
	: mLogBuffer(aLogBuffer)
	, mDisplay(aDisplay)
	, mImageFiltering(aImageFiltering)
	, mImageSaving(aImageSaving)
{
}


///
/// \brief Destructor
///

DisplayThread::~DisplayThread()
{
}


///
/// \brief Perform white balance on the current buffer then update display
///

void DisplayThread::WhiteBalance(PvBufferConverterRGBFilter* aFilterRGB)
{
	// Get the latest buffer - this locks the display thread so we can use the buffer safely
	PvBuffer* lBuffer = RetrieveLatestBuffer();
	if (lBuffer == NULL)
	{
		return;
	}

	PvImage* lFinalImage = lBuffer->GetImage();

	PvBuffer lBufferDisplay;
	PvImage* lImageDisplay = lBufferDisplay.GetImage();
	lImageDisplay->Alloc(lFinalImage->GetWidth(), lFinalImage->GetHeight(), PV_PIXEL_WIN_RGB32);

	// Convert last good buffer to RGB, one-time use converter
	PvBufferConverter lConverter(1);
	lConverter.Convert(lBuffer, &lBufferDisplay);

	aFilterRGB->WhiteBalance(&lBufferDisplay);

	OnBufferDisplay(lBuffer);

	// Important: release the buffer to unlock the display thread
	ReleaseLatestBuffer();
}


///
/// \brief Callback from PvDisplayThread
///

void DisplayThread::OnBufferDisplay(PvBuffer* aBuffer)
{
	PvBuffer* lBuffer = aBuffer;
	if (aBuffer->GetPayloadType() == PvPayloadTypeImage)
	{
		// Range filter
		mImageFiltering->ConfigureConverter(mImageFiltering->GetRangeFilter()->GetConverter());
		lBuffer = mImageFiltering->GetRangeFilter()->Process(aBuffer);
	}

	PvString image_compression_mode;
	auto pv_result = aDeviceParameters->GetEnumValue("ImageCompressionMode", image_compression_mode);
	bool compress_mode = false;
	if (pv_result.IsOK()) {
		if (std::string(image_compression_mode.GetAscii()) == "Lossless") {
			compress_mode = true;
		}
	}

	auto x = aBuffer->GetBlockID();
	if (compress_mode) {
#ifdef DEBUG_LOSSLESS
		std::string fname = std::to_string(aBuffer->GetImage()->GetTimestamp()) + std::string("_bid") + std::to_string(aBuffer->GetBlockID());
#endif

		auto type = aBuffer->GetImage()->GetPixelType();
		uint16_t width = aBuffer->GetImage()->GetWidth();

		//PvBuffer->OvImage#GetHeight()で取得できる値は圧縮後のHeight
		//圧縮前のHeightが必用なためaParameters_から取得
		int64_t before_compressed_height = 0;
		auto feature_height = aDeviceParameters->GetInteger("Height");
		if (feature_height) {
			auto pv_result = feature_height->GetValue(before_compressed_height);
		}

		PvBuffer nBuffer;
		nBuffer.GetImage()->Alloc(width, static_cast<const uint32_t> (before_compressed_height), (PvPixelType)type);
#ifdef DEBUG_LOSSLESS
		auto compressed = std::make_unique<jaids::lossless::CompressedBufferBpp8d>((uint8_t*)aBuffer->GetImage()->GetDataPointer(), width, static_cast<const uint16_t>(before_compressed_height), aBuffer->GetBlockID());
#else
		auto compressed = std::make_unique<jaids::lossless::CompressedBufferBpp8>((uint8_t*)aBuffer->GetImage()->GetDataPointer(), width, static_cast<const uint16_t>(before_compressed_height));
#endif
		try
		{
#ifdef DEBUG_LOSSLESS
			//PvBufferWriter writer;
			//auto fnamee = fname + ".bin";
			//auto result = writer.Store(aBuffer, fnamee.c_str(), PvBufferFormatRaw);
#endif
			compressed->DoDecompress(nBuffer.GetImage()->GetDataPointer());
		}
		catch (const std::exception&)
		{
#ifdef DEBUG_LOSSLESS
			PvBufferWriter writer;
			auto fnamee = fname + "_error.bin";
			auto result = writer.Store(aBuffer, fnamee.c_str(), PvBufferFormatRaw);
			result = aDeviceParameters->ExecuteCommand("AcquisitionStop");
			/* 2022/06/27
			MessageBox(NULL, TEXT("Invalid data"),
				TEXT("メッセージボックス"), MB_ICONERROR); */
			assert(false);
#endif
		}

		// Display
		mImageFiltering->ConfigureConverter(mDisplay->GetConverter());
		mDisplay->Display(nBuffer, GetVSyncEnabled());
	}
	else {
		// Display
		mImageFiltering->ConfigureConverter(mDisplay->GetConverter());
		mDisplay->Display(*lBuffer, GetVSyncEnabled());
	}


	// Will save if format matches displayed images and meet throttling criteria
	if (mImageSaving->GetEnabled())
	{
		mImageSaving->SetDisplaySaved(true);
		PvBuffer* lInternalBuffer = &mDisplay->GetInternalBuffer();
		if (lInternalBuffer != NULL)
		{
			mImageSaving->SaveDisplay(lInternalBuffer, this);
			mDisplay->ReleaseInternalBuffer();
		}
	}
}


///
/// \brief Buffer logging callback. Just add to buffer log.
///

void DisplayThread::OnBufferLog(const PvString& aLog)
{
	mLogBuffer->Log(aLog.GetAscii());
}


///
/// \brief Callback from PvDisplayThread
///

void DisplayThread::OnBufferRetrieved(PvBuffer* aBuffer)
{
	PVUNREFPARAM(aBuffer);

	SetBufferLogErrorEnabled(mLogBuffer->IsBufferErrorEnabled());
	SetBufferLogAllEnabled(mLogBuffer->IsBufferAllEnabled());
	SetChunkLogEnabled(mLogBuffer->IsChunkEnabled());
	SetTapGeometry(mImageFiltering->GetTapGeometry());
}


///
/// \brief Callback from PvDisplayThread
///

void DisplayThread::OnBufferDone(PvBuffer* aBuffer)
{
	// Will save if format matches pure images and meet throttling criteria
	if (mImageSaving->GetEnabled())
	{
		if (mImageSaving->GetFormat() == ImageSaving::FormatBmp)
		{
			mImageSaving->SaveBMP(aBuffer);
		}
		else
		{
			mImageSaving->SavePure(aBuffer);
		}
		mImageSaving->SetDisplaySaved(false);
	}
}


///
/// \brief Callback from PvDisplayThread
///

void DisplayThread::OnBufferTextOverlay(const PvString& aText)
{
	mDisplay->SetTextOverlay(aText);
}


///
/// \brief Returns true if the image filtering configuration has changed
///

bool DisplayThread::HasChanged()
{
	// Save filter configuration to writer
	PvPropertyList lList;
	Save(lList);
	PvConfigurationWriter lWriter;
	lWriter.Store(&lList);

	// Save configuration to a string
	PvString lNow;
	lWriter.SaveToString(lNow);

	// Compare what we now have with the baseline
	return mBaseline != lNow;
}


///
/// \brief Resets the configuration baseline for HasChanged test
///

void DisplayThread::ResetChanged()
{
	// Save filter configuration to writer
	PvPropertyList lList;
	Save(lList);
	PvConfigurationWriter lWriter;
	lWriter.Store(&lList);

	// Save configuration baseline to a string
	lWriter.SaveToString(mBaseline);
}


void DisplayThread::SaveInternalBuffer()
{
	PvBuffer* lInternalBuffer = &mDisplay->GetInternalBuffer();
	if (lInternalBuffer != NULL)
	{
		mImageSaving->SaveDisplay(lInternalBuffer, this, true);
		mDisplay->ReleaseInternalBuffer();
	}
}

void DisplayThread::SetDeviceParameterArray(PvGenParameterArray* aParameters)
{
	aDeviceParameters = aParameters;
}


