
// Sat.h : main header file for the Sat application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSatApp:
// See Sat.cpp for the implementation of this class
//

class CSatApp : public CWinAppEx
{
public:
	CSatApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSatApp theApp;
