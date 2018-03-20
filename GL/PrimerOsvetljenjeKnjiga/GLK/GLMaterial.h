#pragma once
#include "GL\gl.h"

class CGLMaterial
{
protected:
	float ambient[4];
	float diffusion[4];
	float specular[4];
	float shininess;
	float emmision[4];
public:
	CGLMaterial(void);
	virtual ~CGLMaterial(void);
	void Select();
	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetShininess(float shininess);
	void SetEmmision(float r, float g, float b, float a);
};
