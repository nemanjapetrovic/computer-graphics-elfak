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
CTex *tex1,*tex2,*tex3,*tex4,*tex5,*tex6;
CGLRenderer::CGLRenderer(void)
{
	tex1 = new CTex();
	tex2 = new CTex();
	tex3 = new CTex();
	tex4 = new CTex();
	tex5 = new CTex();
	tex6 = new CTex();
}

CGLRenderer::~CGLRenderer(void)
{
	tex1->Release();
	tex2->Release();
	tex3->Release();
	tex4->Release();
	tex5->Release();
	tex6->Release();
	delete tex1, tex2, tex3, tex4, tex5, tex6;
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

	tex1->PrepareTexture(false);
	tex2->PrepareTexture(false);
	tex3->PrepareTexture(false);
	tex4->PrepareTexture(false);
	tex5->PrepareTexture(false);
	tex6->PrepareTexture(false);	

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10.0,5.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
	CString tek[]
	{
		(CString)"brick0.png",
		(CString)"brick01.png",
		(CString)"brick1.png",
		(CString)"brick2.png",
		(CString)"brick3.png",
		(CString)"brick4.png"
	};
	DrawFigure(7.0, 1.0, 87, 87, tek);

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

void CGLRenderer::DrawRoller(float r, float h, int n) 
{
	int i = 0;
	//telo valjka
	glBegin(GL_QUAD_STRIP);
	for (float angle = 0; angle <= 360; angle += (360 / n))
	{
		glNormal3f(cos(toRad(angle)), 0.0, sin(toRad(angle)));
		glTexCoord2f((float)i / n, 0.0);
		glVertex3f(r * cos(toRad(angle)), -h / 2, r * sin(toRad(angle)));
		
		glNormal3f(cos(toRad(angle)), 0.0, sin(toRad(angle)));
		glTexCoord2f(((float)i + 1) /n , 1.0);
		glVertex3f(r * cos(toRad(angle)), h / 2, r * sin(toRad(angle)));
		i++;
	}
	glEnd();

	//gore osnova
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, h / 2, 0.0);
	for (float angle = 0; angle <= 360; angle += (360 / n))
	{
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(r * cos(toRad(angle)), h / 2, r * sin(toRad(angle)));
	}
	glEnd();

	//dole osnova
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, -h / 2, 0.0);
	for (float angle = 0; angle <= 360; angle += (360 / n))
	{
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(r *cos(toRad(angle)), -h / 2, r * sin(toRad(angle)));
	}
	glEnd();
}

void CGLRenderer::DrawFigure(float h, float dx, float alfa, float beta, CString arTex[]) 
{	
	tex1->LoadTexture(arTex[0]);
	tex2->LoadTexture(arTex[1]);
	tex3->LoadTexture(arTex[2]);
	tex4->LoadTexture(arTex[3]);
	tex5->LoadTexture(arTex[4]);
	tex6->LoadTexture(arTex[5]);

	int n = 100;
	float ukupnaVisina = (0.2 * h) + h + (0.2 * h) + (0.2 * h);
	
	//gore osovina
	tex1->Select();
	glPushMatrix();
		glTranslatef(0.0, (ukupnaVisina / 2) - (0.1 * h), 0.0);
		DrawRoller(dx, 0.2 * h, n);
	glPopMatrix();

	// --- Za rotaciju celog elementa
	glPushMatrix();
		glRotatef(alfa, 0.0, 1.0, 0.0);
	
		//dole ispod osovine
		tex2->Select();
		glPushMatrix();
			glTranslatef(0.0, (ukupnaVisina / 2) - (0.2 * h) - (0.1 * h), 0.0);
			DrawRoller(10 * dx, 0.2*h, n);
		glPopMatrix();

		// --- Za rotaciju stubova
		glPushMatrix();	
			glRotatef(beta, 0.0, 1.0, 0.0);

			//stub napred
			tex3->Select();
			glPushMatrix();
				glTranslatef(0.0, (ukupnaVisina / 2) - (0.2*h) - (0.2*h) - (h / 2), 3 * dx);
				DrawRoller(dx, h, n);
				glTranslatef(0.0, -((h / 2) + (0.1*h)), 0.0);
				DrawRoller(0.2*dx, 0.2*h, n);
			glPopMatrix();

			//stub desno
			tex4->Select();
			glPushMatrix();
				glTranslatef(3*dx, (ukupnaVisina / 2) - (0.2*h) - (0.2*h) - (h/2), 0.0);
				DrawRoller(dx, h, n);
				glTranslatef(0.0, -((h / 2) + (0.1*h)), 0.0);
				DrawRoller(0.2*dx, 0.2*h, n);
			glPopMatrix();

			//stub nazad
			tex5->Select();
			glPushMatrix();
				glTranslatef(0.0, (ukupnaVisina / 2) - (0.2*h) - (0.2*h) - (h / 2), -3*dx);
				DrawRoller(dx, h, n);
				glTranslatef(0.0, -((h / 2) + (0.1*h)), 0.0);
				DrawRoller(0.2*dx, 0.2*h, n);
			glPopMatrix();

			//stub levo
			tex6->Select();
			glPushMatrix();
				glTranslatef(-3 * dx, (ukupnaVisina / 2) - (0.2*h) - (0.2*h) - (h / 2), 0.0);
				DrawRoller(dx, h, n);
				glTranslatef(0.0, -((h / 2) + (0.1*h)), 0.0);
				DrawRoller(0.2*dx, 0.2*h, n);
			glPopMatrix();
		
		glPopMatrix();//za rotaciju stubova

	glPopMatrix();//za rotaciju celog elementa
}

float CGLRenderer::toRad(float angle) 
{
	return (angle * M_PI) / 180;
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
