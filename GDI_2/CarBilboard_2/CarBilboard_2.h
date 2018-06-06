
// CarBilboard_2.h : main header file for the CarBilboard_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCarBilboard_2App:
// See CarBilboard_2.cpp for the implementation of this class
//

class CCarBilboard_2App : public CWinAppEx
{
public:
	CCarBilboard_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCarBilboard_2App theApp;
