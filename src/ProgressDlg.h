// *****************************************************************************
//
//     Copyright (c) 2008, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************

#pragma once

#include "Resource.h"

#include <IProgress.h>
#include <Task.h>


class ProgressDlg : public CDialog, public IProgress
{
    DECLARE_DYNAMIC( ProgressDlg )

public:

    ProgressDlg( CWnd* aParentWnd = NULL );
    virtual ~ProgressDlg();
        
    int RunTask( Task *aTask );

    void SetStatus( const std::string &aStatus );
    void SetTitle( const PvString &aTitle ) { mTitle = aTitle.GetUnicode(); }
    void SetCancellable( bool aCancellable );
    void ShowWarning( const std::string &aStatus );

    bool IsCancelled() const { return mCancelled; }

    enum { IDD = IDD_OPENSTREAM };

protected:

    virtual void DoDataExchange(CDataExchange* pDX);
    void OnOK();
    void OnCancel();
    BOOL OnInitDialog();
    afx_msg void OnTimer( UINT_PTR nIDEvent );
    afx_msg void OnDestroy();
    afx_msg void OnCancelButtonClicked();
    DECLARE_MESSAGE_MAP()

    static unsigned long WINAPI Link( void *aParam );

    void Update();

    CStatic mStatusLabel;
    CBitmap mWheelBitmap;
    CButton mCancelTaskButton;

    UINT_PTR mTimer;

    DWORD mWheelIndex;

private:

    CString mTitle;
    CString mStatus;
    CMutex mMutex;

    Task *mTask;

    HANDLE mThreadHandle;

    bool mCancellable;
    bool mCancelled;

};

