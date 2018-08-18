
// Cvet_3.h : main header file for the Cvet_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCvet_3App:
// See Cvet_3.cpp for the implementation of this class
//

class CCvet_3App : public CWinAppEx
{
public:
	CCvet_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCvet_3App theApp;
