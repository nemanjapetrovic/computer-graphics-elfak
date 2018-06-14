
// Cvet_2.h : main header file for the Cvet_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCvet_2App:
// See Cvet_2.cpp for the implementation of this class
//

class CCvet_2App : public CWinAppEx
{
public:
	CCvet_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCvet_2App theApp;
