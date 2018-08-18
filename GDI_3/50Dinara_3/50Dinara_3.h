
// 50Dinara_3.h : main header file for the 50Dinara_3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy50Dinara_3App:
// See 50Dinara_3.cpp for the implementation of this class
//

class CMy50Dinara_3App : public CWinAppEx
{
public:
	CMy50Dinara_3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy50Dinara_3App theApp;
