
// Circles.h : main header file for the Circles application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCirclesApp:
// See Circles.cpp for the implementation of this class
//

class CCirclesApp : public CWinAppEx
{
public:
	CCirclesApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCirclesApp theApp;
