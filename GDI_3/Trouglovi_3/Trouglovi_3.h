
// Trouglovi_3.h : main header file for the Trouglovi_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTrouglovi_3App:
// See Trouglovi_3.cpp for the implementation of this class
//

class CTrouglovi_3App : public CWinAppEx
{
public:
	CTrouglovi_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrouglovi_3App theApp;
