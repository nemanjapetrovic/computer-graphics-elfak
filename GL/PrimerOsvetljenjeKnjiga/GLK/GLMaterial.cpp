#include "stdafx.h"
#include "GLMaterial.h"
#include "GL\gl.h"

CGLMaterial::CGLMaterial(void)
{
	//GL_AMBIENT_DEFAULT
	ambient[0] = 0.2;
	ambient[1] = 0.2;
	ambient[2] = 0.2;
	ambient[3] = 1.0;

	//GL_DIFFUSE_DEFAULT
	diffusion[0] = 0.8;
	diffusion[1] = 0.8;
	diffusion[2] = 0.8;
	diffusion[3] = 1.0;

	//GL_SPECULAR_DEFAULT
	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
	specular[3] = 0.0;

	//GL_SHININESS_DEFAULT
	shininess = 128.0;

	//GL_EMMISION_DEFAUL
	emmision[0] = 0.0;
	emmision[1] = 0.0;
	emmision[2] = 0.0;
	emmision[3] = 1.0;
}
  

CGLMaterial::~CGLMaterial(void)
{
}

void CGLMaterial::Select()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusion);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emmision);
}
void CGLMaterial::SetAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void CGLMaterial::SetDiffuse(float r, float g, float b, float a)
{
	diffusion[0] = r;
	diffusion[1] = g;
	diffusion[2] = b;
	diffusion[3] = a;
}
void CGLMaterial::SetSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void CGLMaterial::SetShininess(float s)
{
	if (s > 128.0)
		shininess = 128.0;
	else if (s < 0.0)
		shininess = 0.0;
	else
		shininess = s;
}
void CGLMaterial::SetEmmision(float r, float g, float b, float a)
{
	emmision[0] = r;
	emmision[1] = g;
	emmision[2] = b;
	emmision[3] = a;
}