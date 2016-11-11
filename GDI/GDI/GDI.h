
// GDI.h : main header file for the GDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDIApp:
// See GDI.cpp for the implementation of this class
//

class CGDIApp : public CWinApp
{
public:
	CGDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDIApp theApp;
