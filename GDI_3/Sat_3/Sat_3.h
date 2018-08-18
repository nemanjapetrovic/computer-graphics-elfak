
// Sat_3.h : main header file for the Sat_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSat_3App:
// See Sat_3.cpp for the implementation of this class
//

class CSat_3App : public CWinAppEx
{
public:
	CSat_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSat_3App theApp;
