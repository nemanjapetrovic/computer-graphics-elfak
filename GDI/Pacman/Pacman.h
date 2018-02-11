
// Pacman.h : main header file for the Pacman application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPacmanApp:
// See Pacman.cpp for the implementation of this class
//

class CPacmanApp : public CWinAppEx
{
public:
	CPacmanApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPacmanApp theApp;
