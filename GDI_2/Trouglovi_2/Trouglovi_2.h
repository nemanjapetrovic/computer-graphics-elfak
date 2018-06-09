
// Trouglovi_2.h : main header file for the Trouglovi_2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTrouglovi_2App:
// See Trouglovi_2.cpp for the implementation of this class
//

class CTrouglovi_2App : public CWinAppEx
{
public:
	CTrouglovi_2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrouglovi_2App theApp;
