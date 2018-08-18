#include "stdafx.h"
#include "MipMap.h"
#include "DImage.h"

CMipMap::CMipMap(CString imageName)
{
	img = new DImage();
	img->Load(imageName);
}


CMipMap::~CMipMap()
{
	delete img;
}

CDC* CMipMap::DrawToDC(CDC *pDC, CRect rect)
{
	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	//draw..
	int w = img->Width();
	int h = img->Height();
	int startX = 0;
	int startY = 0;
	int endX = img->Width();
	int endY = img->Height();
	while (w > 1 && h > 1)
	{
		CRect drawingRect(startX,startY,endX,endY);
		img->Draw(memDC, CRect(0, 0, img->Width(), img->Height()), drawingRect);

		//podesi poziciju za crtanje
		startX += w;
		startY += h / 2;
		endX += w / 2;
		endY = endY;

		//smanji velicinu sledece slike
		w = w / 2;
		h = h / 2;		
	}
	//draw..

	return memDC;
}

CDC* CMipMap::DrawMipMap(CDC *pDC, CRect rect, int x, int y, int size)
{
	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	CRect drawingRect(x, y, x + size, y + size);
	img->Draw(memDC, CRect(0,0,img->Width(),img->Height()), drawingRect);

	return memDC;
}