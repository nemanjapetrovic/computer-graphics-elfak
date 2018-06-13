#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	double R(double a, double alpha, int n, double h);
	void NormCrossProd(double x1, double y1, double z1, double x2, double y2, double z2, double& x, double& y, double& z);
	
	void DrawPrism(float x, float y, float z);
	void SetMaterial(float r, float g, float b);
	void SetLight(float x, float y, float z, float dx, float dy, float dz);
	void DrawFigure(float length, float base, float height, float offset, float angle, COLORREF arColors[], CString arTextures[]);
protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

};
