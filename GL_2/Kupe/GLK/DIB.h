/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jorge Lodos
// All rights reserved
//
// Distribute and use freely, except:
// 1. Don't alter or remove this notice.
// 2. Mark the changes you made
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    lodos@cigb.edu.cu
/////////////////////////////////////////////////////////////////////////////

// dib.h

#ifndef _INC_DIB
#define _INC_DIB

/* DIB constants */
#define PALVERSION   0x300

/* Dib Header Marker - used in writing DIBs to files */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/* DIB Macros*/
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

class CDib : public CObject
{
	DECLARE_DYNAMIC(CDib)

// Constructors
public:
	CDib();
	CDib(CBitmap& bitmap);
	CDib(CBitmap* bitmap);

// Attributes
	LPBITMAPINFO m_pBMI;
	LPBYTE m_pBits;	
public:	
	CPalette* m_pPalette;

public:
	DWORD Width();
	DWORD Height();
	WORD  NumColors();
	BOOL  IsValid() { return (m_pBMI != NULL); }

// Operations
public:
	BOOL  Paint(HDC hDC, CRect rcDC, CRect rcDIB);
	HGLOBAL CopyToHandle();
	DWORD Save(CFile& file);
	DWORD Save(char* filename);
	DWORD Read(CFile& file);
	DWORD Read(char* filename);
	DWORD ReadFromHandle(HGLOBAL hGlobal);
	void  Invalidate() { Free(); }

	virtual void Serialize(CArchive& ar);
	

// Implementation
public:
	virtual ~CDib();

protected:
	BOOL  CreatePalette();
	WORD  PaletteSize();
	void Free();

public:
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc);
#endif

protected:
	CDib& operator = (CDib& dib);
};

#endif //!_INC_DIB
