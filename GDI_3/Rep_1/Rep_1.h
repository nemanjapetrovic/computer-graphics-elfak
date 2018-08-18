
// Rep_1.h : main header file for the Rep_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRep_1App:
// See Rep_1.cpp for the implementation of this class
//

class CRep_1App : public CWinApp
{
public:
	CRep_1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRep_1App theApp;
