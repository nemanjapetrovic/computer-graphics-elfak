
// Circles_3.h : main header file for the Circles_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCircles_3App:
// See Circles_3.cpp for the implementation of this class
//

class CCircles_3App : public CWinAppEx
{
public:
	CCircles_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCircles_3App theApp;
