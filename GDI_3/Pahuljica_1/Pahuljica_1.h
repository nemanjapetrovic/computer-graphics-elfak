
// Pahuljica_1.h : main header file for the Pahuljica_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPahuljica_1App:
// See Pahuljica_1.cpp for the implementation of this class
//

class CPahuljica_1App : public CWinAppEx
{
public:
	CPahuljica_1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPahuljica_1App theApp;
