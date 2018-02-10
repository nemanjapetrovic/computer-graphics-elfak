#pragma once

#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

class DImage
{
public:
	DImage(void);
	DImage(CBitmap& bmp);
	virtual ~DImage(void);

	bool	Load(CString fileName); // Ucitava sliku iz datoteke cije se ime navodi
	bool	Save(CString fileName); // Upisuje sliku u datoteku cije se ime navodi
	void	Draw(CDC* pDC, CRect rcImg, CRect rcDC); // Iscrtava sliku u datom DC-ju

	int		Width(){return m_nWidth;}	// Sirina u pikselima
	int		Height(){return m_nHeight;} // Visina u pikselima
	int		BPP(){return m_nBPP;}						// Broj bajtova po pikselu
	
	bool	isValid(){return m_pBuf!=NULL;}
	
	// Direktne izmene
	unsigned char* GetDIBBits(){return m_pBuf;} // Vraca pointer na prvi bajt sa pikselima
	void	Update();		// Pozvati nakon direktne izmene bafera.
	
protected:
	void Flip();
	void Convert(int oldBPP, int newBPP);
	void Save(CFile& file);
	int m_nWidth;
	int m_nHeight;
	int m_nBPP;
	int GetScanlineWidth(){return ((m_nWidth*m_nBPP+3)/4)*4;}
	unsigned char* m_pBuf;
	CBitmap* m_pBmp;
};
