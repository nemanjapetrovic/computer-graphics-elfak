
// 50Dinara.h : main header file for the 50Dinara application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy50DinaraApp:
// See 50Dinara.cpp for the implementation of this class
//

class CMy50DinaraApp : public CWinAppEx
{
public:
	CMy50DinaraApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy50DinaraApp theApp;
