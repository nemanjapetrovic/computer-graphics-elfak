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

CGLRenderer::CGLRenderer(void)
{
}

CGLRenderer::~CGLRenderer(void)
{
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
	glEnable(GL_LIGHTING);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//svetlo
	float l1_ambient[] = { 0.2,0.2,0.2,1.0 };
	float l1_diffuse[] = { 1.0,1.0,1.0,1.0 };
	float l1_specular[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_specular);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHT1);

	float l1_position[] = { 5.0,3.0,5.0,1.0 };
	float l1_direction[] = { -1.0,-1.0,0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, l1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1_direction);

	//crtanje
	float h = 1.0;
	float r = 0.5;

	//dole
	glPushMatrix();
		glTranslatef(0.0, -h / 2, 0.0);	
		DrawCone(r, h);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, -(h + h / 2), 0.0);
		glRotatef(180.0, 1.0, 0.0, 0.0);
		DrawCone(r, h);
	glPopMatrix();

	//desno
	glPushMatrix();
		glRotatef(30.0, 0.0, 1.0, 0.0);
		
		glPushMatrix();	
			glTranslatef(h / 2, 0.0, 0.0);		
			glRotatef(90.0,0.0,0.0,1.0);
			DrawCone(r, h);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef((h + (h / 2)), 0.0, 0.0);		
			glRotatef(-90, 0.0, 0.0, 1.0);
			DrawCone(r, h);
		glPopMatrix();

	glPopMatrix();

	//levo
	glPushMatrix();
		glRotatef(-30, 0.0, 1.0, 0.0);

		glPushMatrix();
			glTranslatef(-h / 2, 0.0, 0.0);		
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			DrawCone(r, h);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-(h + (h / 2)), 0.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			DrawCone(r, h);
		glPopMatrix();
		
	glPopMatrix();

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

void CGLRenderer::DrawCone(double r, double h)
{
	float ambient[] = { 0.2,0.2,0.2,1.0 };
	float diffuse[] = { 0.5,0.5,0.5,1.0 };
	float emission[] = { 0.5, 0.5, 0.5,1.0 };
	float shinnines = 128;
	float specular[] = { 0.5,0.5,0.5,1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinnines);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	float nas = r;
	float nal = h;
	float tanUgla = nas / nal;
	float coneAngle = (atan(tanUgla) * 180) / M_PI;

	//telo
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, h / 2, 0.0);
		for (float angle = 0; angle <= 360; angle += 2) 
		{			
			glNormal3f(cos(toRad(coneAngle)) * cos(toRad(angle)), sin(toRad(coneAngle)), cos(toRad(coneAngle)) * sin(toRad(angle)));
			glVertex3f(r * cos(toRad(angle)), -h / 2, r * sin(toRad(angle)));
		}
	glEnd();
	
	//osnova
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(0.0, -h / 2, 0.0);
		for (float angle = 0; angle <= 360; angle += 2) 
		{
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(r * cos(toRad(angle)), -h / 2, r * sin(toRad(angle)));
		}
	glEnd();
}

float CGLRenderer::toRad(float angle) {
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
