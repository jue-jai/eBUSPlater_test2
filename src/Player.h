// *****************************************************************************
//
//     Copyright (c) 2013, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <IPlayerController.h>
#include <IProgress.h>
#include <Device.h>
#include <Stream.h>
#include <ImageFiltering.h>
#include <Setup.h>

#include <PvDeviceGEV.h>
#include <PvDeviceU3V.h>
#include <PvLogger.h>

#ifdef SERIALBRIDGE
#include <PvCameraBridgeManagerWnd.h>
#include <PvSerialBridgeManagerWnd.h>
#else
#include <PvCameraBridge.h>
#endif


class PvSystem;

struct DeviceAttributes 
{
    void Reset()
    {
        mVendor = "";
        mModel = "";
        mName = "";
        mIP = "";
        mMAC = "";
        mGUID = "";
        mConnectionID = "";
    }

    PvString mConnectionID;
    PvString mVendor;
    PvString mModel;
    PvString mName;
    PvString mIP;
    PvString mMAC;
    PvString mGUID;
};


class Player
{
#ifdef _AFXDLL
    DECLARE_DYNAMIC( Player )
#endif // _AFXDLL

public:

    Player( IPlayerController *aController, IPvDisplayAdapter *aDisplay );
    ~Player();

    bool IsControlledTransmitter() { return ( mDevice != NULL ) && mDevice->IsTransmitter(); }
    bool IsDeviceConnected() { return ( mDevice != NULL ) && mDevice->IsConnected(); }
    bool IsDeviceFrameGrabber() { return ( mDevice != NULL ) && mDevice->IsFrameGrabber(); }
    bool IsStreamOpened();
    bool IsStreamStarted();
    bool IsStreaming() { return IsDeviceConnected() && mDevice->IsStreaming(); }
    bool IsSerialSupported() { return IsDeviceConnected() && mDevice->IsSerialSupported(); }
    bool IsLinkRecoveryEnabled();
    bool IsStreamRequiresReopen();

    bool HavePreferencesChanged() const;
    void ResetPreferencesChanged();

    void ResetSetup() { mSetup.Reset(); }
    Setup::Role GetSetupRole() const { return mSetup.GetRole(); }
    bool IsSetupRoleDataReceiver() const { return mSetup.IsDataReceiver(); }
    bool IsSetupRoleController() const { return mSetup.IsController(); }

#ifdef SERIALBRIDGE
    PvCameraBridgeManagerWnd *GetCameraBridgeManager() { return mCameraBridgeManagerWnd; }
    PvSerialBridgeManagerWnd *GetSerialBridgeManager() { return mSerialBridgeManagerWnd; }
#endif // SERIALBRIDGE

    void GetControlsEnabled( ControlsState &aState );
    void GetDefaultCommunicationParameters( const PvDeviceInfo *aDeviceInfo, PvString &aParameters );
    DeviceAttributes &GetDeviceAttributes() { return mDeviceAttributes; }

    PvResult Connect( const PvDeviceInfo *aDI, PvConfigurationReader *aCR );
    void StartStreaming();
    void Play();
    void Disconnect();
    void Reconnect( const PvString &aConnectionID );
    void StopStreaming();
    void ForceStop();
    void StopIfApplicable();

    void SaveStatus( IProgress *aProgress, PvString &aStatus );
    void LoadStatus( IProgress *aProgress, const PvString &aStatus );

    PvResult ChangeSource( int64_t aNewSource );
    
    Setup *GetSetup() { return &mSetup; }
    LogBuffer *GetLogBuffer() { return &mLogBuffer; }
    DisplayThread *GetDisplayThread() { return mDisplayThread; }
    ImageSaving *GetImageSaving() { return mImageSaving; }
    ImageFiltering *GetImageFiltering() { return mImageFiltering; }
    BufferOptions *GetBufferOptions() { return &mBufferOptions; }

    PvResult OpenConfig( PvConfigurationReader *aReader, PvStringList &aErrorList, bool aShowProgress );
    PvResult SaveConfig( PvConfigurationWriter *aWriter, PvStringList &aErrorList, bool aSaveConnectedDevice );
    bool IsSameAsCurrent( PvConfigurationReader *aReader );

    void GetStatusText( PvString &aText, bool &aRecording );

    void SaveCurrentImage();
    PvString GetDeviceXMLDefaultName();
    PvResult SaveDeviceXML( const PvString &aFilename );
    
    PvDevice *GetPvDevice();
    IPvDeviceAdapter *GetPvDeviceAdapter();

    void GetSources( ComboItemVector &aSources );
    void GetCurrentAcquisitionMode( ComboItem &aMode, bool &aWritable );
    void GetAcquisitionModes( ComboItemVector &aModes, bool &aWritable );
    PvResult SetAcquisitionMode( int64_t aNewMode );

    bool DoBufferOptionsRequireApply();
    PvResult ApplyBufferOptions();

    void ResetUpdatingStream();
    void ResetUpdatingAcquisitionMode();
	void ResetStreamingStatistics();

    void UpdateAttributes( const PvDeviceInfo *aDI );
    void UpdateController();

    static PvGenParameterArray *GetDefaultGEVCommunicationParameters() { return sDefaultDeviceGEV.GetCommunicationParameters(); }
    static PvGenParameterArray *GetDefaultU3VCommunicationParameters() { return sDefaultDeviceU3V.GetCommunicationParameters(); }
    static BufferOptions *GetDefaultBufferOptions() { return &sDefaultBufferOptions; }
    
    PvGenParameterArray *GetCommunicationParameters();
    PvGenParameterArray *GetDeviceParameters();
    PvGenParameterArray *GetStreamParameters();

    PvResult ReconnectTaskHandler( IProgress *aProgress, const PvString &aConnectionID );
    PvResult OpenConfigTaskHandler( IProgress *aProgress, PvConfigurationReader *lReader, PvStringList &aErrorList );
    PvResult SaveConfigTaskHandler( IProgress *aProgress, PvConfigurationWriter *lWriter, PvStringList &aErrorList, bool aSaveConnectedDevice );
    PvResult ChangeSourceTaskHandler( IProgress *aProgress, int64_t aNewSource );

    PvResult ConnectTaskHandler( IProgress *aProgress, const PvDeviceInfo *aDI, PvConfigurationReader *aCR = NULL, PvStringList *aErrorList = NULL );
    // ------------------------------
    PvResult ConnectController( IProgress *aProgress, const PvDeviceInfo *aDI, uint16_t &aChannel );
    PvResult ConnectController( IProgress *aProgress, PvConfigurationReader *aCR );
    PvResult OpenDataReceiver( IProgress *aProgress, const PvDeviceInfo *aDI, uint16_t aChannel );
    PvResult OpenDataReceiver( IProgress *aProgress, PvConfigurationReader *aCR, uint16_t &aChannel );
    PvResult GetDeviceInfo( IProgress *aProgress, PvSystem &aSystem, const PvDeviceInfo **aDI );
    PvResult SetStreamDestination( IProgress *aProgress, uint16_t aChannel );
    void CreateBridges();

    PvResult DisconnectTaskHandler( IProgress *aProgress );
    // ------------------------------
    void PreDisconnect( IProgress *aProgress );
    void CloseStream( IProgress *aProgress );
    void CloseBridges( IProgress *aProgress );
    void DisconnectDevice( IProgress *aProgress );

protected:

    PvCameraBridge *GetSelectedBridge();

    PvResult LoadBridges( IProgress *aProgress, PvConfigurationReader *aReader, PvStringList &aErrorList );
    PvResult SaveBridges( IProgress *aProgress, PvConfigurationWriter *aWriter, PvStringList &aErrorList );

private:

    IPlayerController *mController;

    PvDeviceInfo *mDeviceInfo;
    Device *mDevice;
    
    Stream *mStream;
    Mutex mStreamMutex;

    Setup mSetup;
    LogBuffer mLogBuffer;
    DisplayThread *mDisplayThread;
    ImageSaving *mImageSaving;
    ImageFiltering *mImageFiltering;
    BufferOptions mBufferOptions;

    static PvDeviceGEV sDefaultDeviceGEV;
    static PvDeviceU3V sDefaultDeviceU3V;
    static BufferOptions sDefaultBufferOptions;

    bool mChangingSource;
    int32_t mPreferredSource;

    PvLogger mLogger;

#ifdef SERIALBRIDGE
    PvCameraBridgeManagerWnd *mCameraBridgeManagerWnd;
    PvSerialBridgeManagerWnd *mSerialBridgeManagerWnd;
#endif // SERIALBRIDGE

    DeviceAttributes mDeviceAttributes;
    ChangedList mChangedList;

};


#endif // __PLAYER_H__

