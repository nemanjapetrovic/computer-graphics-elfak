
// Suriken_2.h : main header file for the Suriken_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSuriken_2App:
// See Suriken_2.cpp for the implementation of this class
//

class CSuriken_2App : public CWinAppEx
{
public:
	CSuriken_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSuriken_2App theApp;
