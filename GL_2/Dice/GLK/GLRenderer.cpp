#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
#include "Tex.h"


//#pragma comment(lib, "GL\\glut32.lib")

const double M_PI = 3.141592653589793238463;
CTex *tekstura;

CGLRenderer::CGLRenderer(void)
{
	tekstura = new CTex();
}

CGLRenderer::~CGLRenderer(void)
{
	tekstura->Release();
	delete tekstura;
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	tekstura->PrepareTexture(false);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	tekstura->LoadTexture((CString)"brick.png");
	tekstura->Select();

	ThrowDice(2.0);

	glFlush();
	SwapBuffers(pDC->m_hDC);

	//---------------------------------	
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	double aspect = (double)w / (double)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawDice(float a)
{
	float vert[72] =
	{
		//napred
		-a/2,-a/2,a/2, //0
		a/2,-a/2,a/2,  //1
		a/2,a/2,a/2,   //2
		-a/2,a/2,a/2,  //3
		//desno
		a/2,-a/2,a/2, //1
		a/2,-a/2,-a/2, //4
		a/2,a/2,-a/2, //7
		a/2,a/2,a/2, //2
		//nazad
		a/2,-a/2,-a/2, //4
		-a/2,-a/2,-a/2, //5
		-a/2,a/2,-a/2, //6
		a/2,a/2,-a/2, //7
		//levo
		-a/2,-a/2,-a/2,//5
		-a/2,-a/2,a/2,//0
		-a/2,a/2,a/2,//3
		-a/2,a/2,-a/2,//6
		//gore
		-a/2,a/2,a/2,//3
		a/2,a/2,a/2,//2
		a/2,a/2,-a/2,//7
		-a/2,a/2,-a/2,//6
		//dole
		-a/2,-a/2,a/2,//0
		a/2,-a/2,a/2,//1
		a/2,-a/2,-a/2,//4
		-a/2,-a/2,-a/2//5
	};

	float norm[72]
	{
		//napred
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		//desno
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		//nazad
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		//levo
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		//gore
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		//dole
		0.0,-1.0,0.0,
		0.0,-1.0,0.0,
		0.0,-1.0,0.0,
		0.0,-1.0,0.0
	};

	float tex[48]
	{
		//napred
		1/3,1/3,
		2/3,1/3,
		2/3,2/3,
		1/3,2/3,
		//desno
		2/3,1/3,
		1.0,1/3,
		1.0,2/3,
		2/3,2/3,
		//nazad
		2/3,0.0,
		1.0,0.0,
		1.0,1/3,
		2/3,1/3,
		//levo
		0.0,1/3,
		1/3,1/3,
		1/3,2/3,
		0.0,2/3,
		//gore
		1/3,2/3,
		2/3,2/3,
		2/3,1.0,
		1/3,1.0,
		//dole
		1/3,0.0,
		2/3,0.0,
		2/3,1/3,
		1/3,1/3		
	};

	glVertexPointer(3, GL_FLOAT, 0, vert);
	glNormalPointer(GL_FLOAT, 0, norm);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void CGLRenderer::ThrowDice(float len)
{
	float a = 1.0;
	
	// obicna
	DrawDice(a);

	// ugao rotacije za predjeni put
	float angleRad = len / (2 * M_PI);
	// prebaci ga u stepene
	float angle = (angleRad * 180) / M_PI;
	
	// ugao za koji rotiramo, uvek se vraca na moduo od 90 stepeni
	int rotAngle = (int)angle + (90 - ((int)angle % 90));
	
	// Pomeramo na mesto i rotiramo kocku
	glTranslatef(len, 0.0, 0.0);
	glRotatef(rotAngle, 0.0, 0.0, -1.0);

	DrawDice(a);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

double CGLRenderer::R(double a, double alpha, int n, double h)
{
	alpha *= 0.01745329251994329577;
	double PI2 = 6.2831853071795864769;
	double alpha1 = (PI2 / (2 * n) - alpha);
	double alpha2;
	double R1, R;

	R = a / (2 * sin(alpha1 / 2.0));
	double delta = R / 4.;
	R1 = R;
	do {
		alpha1 = 2 * asin(a / (2 * R1));
		alpha2 = 2 * asin(a / (2 * (R1 - h)));
		if ((alpha1 + alpha2) > ((PI2 / n) - (2 * alpha)))
			R1 += delta;
		else
			R1 -= delta;
		delta /= 2.0;
	} while (delta > 1e-6);
	return R;
}

void CGLRenderer::NormCrossProd(double x1, double y1, double z1, double x2, double y2, double z2, double& x, double& y, double& z)
{
	x = y1 * z2 - z1 * y2;
	y = z1 * x2 - x1 * z2;
	z = x1 * y2 - y1 * x2;
	double d = sqrt(x*x + y*y + z*z);
	if (d != 0.0)
	{
		x /= d; y /= d; z /= d;
	}
}
