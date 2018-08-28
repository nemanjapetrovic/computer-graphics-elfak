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

CTex *t1, *t2, *t3, *t4, *t5, *t6;
CGLRenderer::CGLRenderer(void)
{
	t1 = new CTex();
	t2 = new CTex();
	t3 = new CTex();
	t4 = new CTex();
	t5 = new CTex();
	t6 = new CTex();
}

CGLRenderer::~CGLRenderer(void)
{
	delete t1;
	delete t2;
	delete t3;
	delete t4;
	delete t5;
	delete t6;
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

	t1->PrepareTexture(false);
	t2->PrepareTexture(false);
	t3->PrepareTexture(false);
	t4->PrepareTexture(false);
	t5->PrepareTexture(false);
	t6->PrepareTexture(false);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10.0, 5.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//draw..
	CString tek[]
	{
		(CString)"brick0.png",
		(CString)"brick01.png",
		(CString)"brick1.png",
		(CString)"brick2.png",
		(CString)"brick3.png",
		(CString)"brick4.png"
	};
	DrawFigure(7.0, 1.0, 90, 90, tek);
	//draw..

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
	//telo
	glBegin(GL_QUAD_STRIP);
		for (float angle = 0; angle <= 360; angle += (360 / n))
		{
			//dole
			glNormal3f(r * cos(toRad(angle)), 0.0, r*sin(toRad(angle)));
			glTexCoord2f((float)i / n, 0.0);
			glVertex3f(r * cos(toRad(angle)), -h / 2, r * sin(toRad(angle)));

			//gore
			glNormal3f(r*cos(toRad(angle)), 0.0, r*sin(toRad(angle)));
			glTexCoord2f((float)i / n, 1.0);
			glVertex3f(r *cos(toRad(angle)), h / 2, r*sin(toRad(angle)));
			
			i++;
		}
	glEnd();

	//osnova gore
	i = 0;
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, h / 2, 0.0);		
		for (float angle = 0; angle <= 360; angle += (360 / n)) 
		{
			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2f((float)i / n, 1.0);
			glVertex3f(r * cos(toRad(angle)), h / 2, r * sin(toRad(angle)));

			i++;
		}
	glEnd();

	//osnova dole
	i = 0;
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, -h / 2, 0.0);
		for (float angle = 0; angle <= 360; angle += (360 / n))
		{
			glNormal3f(0.0, -1.0, 0.0);
			glTexCoord2f((float)i / n, 1.0);
			glVertex3f(r * cos(toRad(angle)), -h / 2, r *sin(toRad(angle)));
		}
	glEnd();
}

void CGLRenderer::DrawFigure(float h, float dx, float alfa, float beta, CString arTex[]) 
{
	t1->LoadTexture(arTex[0]);
	t2->LoadTexture(arTex[1]);
	t3->LoadTexture(arTex[2]);
	t4->LoadTexture(arTex[3]);
	t5->LoadTexture(arTex[4]);
	t6->LoadTexture(arTex[5]);

	//osovina
	t1->Select();
	glPushMatrix();
		glTranslatef(0.0, 0.2*h, 0.0);
		DrawRoller(dx, 0.2*h, 300);
	glPopMatrix();

	glPushMatrix();
		
		glRotatef(alfa, 0.0, 1.0, 0.0);
		
		//telo gore
		t2->Select();
		glPushMatrix();	
			DrawRoller(10 * dx, 0.2 * h, 300);
		glPopMatrix();

		glPushMatrix();
			glRotatef(beta, 0.0, 1.0, 0.0);

			//stub napred
			t3->Select();
			glPushMatrix();				
				glTranslatef(0.0, (-0.1 * h) - (h / 2), 3 * dx);
				DrawRoller(dx, h, 300);
				glTranslatef(0.0, -h / 2 - 0.1*h, 0.0);
				DrawRoller(2 * dx, 0.2*h,300);
			glPopMatrix();

			//stub desno
			t4->Select();
			glPushMatrix();
				glTranslatef(3 * dx, (-0.1 * h) - (h / 2), 0.0);
				DrawRoller(dx, h, 300);
				glTranslatef(0.0, -h / 2 - 0.1*h, 0.0);
				DrawRoller(2 * dx, 0.2*h,300);
			glPopMatrix();

			//stub nazad
			t5->Select();
			glPushMatrix();
				glTranslatef(0.0, (-0.1 * h) - (h / 2), -3 * dx);
				DrawRoller(dx, h, 300);
				glTranslatef(0.0, -h / 2 - 0.1*h, 0.0);
				DrawRoller(2 * dx, 0.2*h,300);
			glPopMatrix();

			//stub levo
			t6->Select();
			glPushMatrix();
				glTranslatef(-3 * dx, (-0.1 * h) - (h / 2), 0.0);
				DrawRoller(dx, h, 300);
				glTranslatef(0.0, -h / 2 - 0.1*h, 0.0);
				DrawRoller(2 * dx, 0.2*h,300);
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
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
