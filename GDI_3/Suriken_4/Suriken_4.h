
// Suriken_4.h : main header file for the Suriken_4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSuriken_4App:
// See Suriken_4.cpp for the implementation of this class
//

class CSuriken_4App : public CWinAppEx
{
public:
	CSuriken_4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSuriken_4App theApp;
