
// TestPrimer.h : main header file for the TestPrimer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTestPrimerApp:
// See TestPrimer.cpp for the implementation of this class
//

class CTestPrimerApp : public CWinAppEx
{
public:
	CTestPrimerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTestPrimerApp theApp;
