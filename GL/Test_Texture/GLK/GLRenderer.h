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
	
	void PrepareCube(float a);
	void DrawBrickCube();
	void DrawNamotanaCube();
	void DrawAxes(float size);
	
protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

};
