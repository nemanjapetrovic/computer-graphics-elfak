
// Sat_2.h : main header file for the Sat_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSat_2App:
// See Sat_2.cpp for the implementation of this class
//

class CSat_2App : public CWinAppEx
{
public:
	CSat_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSat_2App theApp;
