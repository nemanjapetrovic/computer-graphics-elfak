
// Tocak_1.h : main header file for the Tocak_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTocak_1App:
// See Tocak_1.cpp for the implementation of this class
//

class CTocak_1App : public CWinAppEx
{
public:
	CTocak_1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTocak_1App theApp;
