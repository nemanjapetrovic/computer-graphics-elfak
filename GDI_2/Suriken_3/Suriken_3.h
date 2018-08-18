
// Suriken_3.h : main header file for the Suriken_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSuriken_3App:
// See Suriken_3.cpp for the implementation of this class
//

class CSuriken_3App : public CWinAppEx
{
public:
	CSuriken_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSuriken_3App theApp;
