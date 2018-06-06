#include "StdAfx.h"
#include "Tex.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"

CTex::CTex()
{
	id = 0;
}


CTex::~CTex()
{
	this->Release();
}

void CTex::PrepareTexture(bool lightEnabled)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (lightEnabled) 
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
}

void CTex::LoadTexture(CString fileName)
{
	if (id) 
	{
		this->Release();
	}

	// Alokacija
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Parametri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Ucitavanje
	DImage *img = new DImage();
	img->Load(fileName);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->Width(), img->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->GetDIBBits());

	delete img;
}

void CTex::Select()
{
	if (id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}

void CTex::Release()
{
	if (id) 
	{
		glDeleteTextures(1, &id);
		id = 0;
	}
}