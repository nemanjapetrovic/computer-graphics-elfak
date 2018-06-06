
// Circles_2.h : main header file for the Circles_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCircles_2App:
// See Circles_2.cpp for the implementation of this class
//

class CCircles_2App : public CWinAppEx
{
public:
	CCircles_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCircles_2App theApp;
