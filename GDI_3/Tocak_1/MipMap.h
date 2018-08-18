#pragma once
#include "DImage.h"

class CMipMap 
{
public:	
	DImage *img;
	CMipMap(CString imageName);
	~CMipMap();
	CDC* DrawToDC(CDC *pDC, CRect rect);
	CDC* DrawMipMap(CDC *pDC, CRect rect, int x, int y, int size);
};

