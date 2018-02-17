
// Trouglovi.h : main header file for the Trouglovi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTrougloviApp:
// See Trouglovi.cpp for the implementation of this class
//

class CTrougloviApp : public CWinAppEx
{
public:
	CTrougloviApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrougloviApp theApp;
