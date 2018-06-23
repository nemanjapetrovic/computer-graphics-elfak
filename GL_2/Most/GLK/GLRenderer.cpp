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
CTex *tex;
CGLRenderer::CGLRenderer(void)
{
	tex = new CTex();
}

CGLRenderer::~CGLRenderer(void)
{
	tex->Release();
	delete tex;
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

	tex->PrepareTexture(false);
	tex->LoadTexture((CString)"brick.png");

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	tex->Select();
	DrawHalfBridge(0.2, 2.0, 1.0, 1.0, 20);
		
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
	gluPerspective(40.0, aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawPrism(float dx, float dy, float dz)
{
	glBegin(GL_QUADS);
	
	//napred
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-dx / 2, -dy / 2, dz / 2);
	glTexCoord2f(1 / 4, 0.0);
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glTexCoord2f(1 / 4, 1);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-dx / 2, dy / 2, dz / 2);

	//desno
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1 / 4, 0.0);
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glTexCoord2f(2 / 4, 0.0);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);
	glTexCoord2f(2 / 4, 1.0);
	glVertex3f(dx / 2, dy / 2, -dz / 2);
	glTexCoord2f(1 / 4, 1.0);
	glVertex3f(dx / 2, dy / 2, dz / 2);

	//nazad
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(2 / 4, 0.0);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);
	glTexCoord2f(3 / 4, 0.0);
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);
	glTexCoord2f(3 / 4, 1.0);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);
	glTexCoord2f(2 / 4, 1.0);
	glVertex3f(dx / 2, dy / 2, -dz / 2);

	//levo
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(3 / 4, 0.0);
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-dx / 2, -dy / 2, dz / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-dx / 2, dy / 2, dz / 2);
	glTexCoord2f(3 / 4, 1.0);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);

	//gore
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, -dz / 2);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);

	//dole
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);

	glEnd();
}

void CGLRenderer::DrawHalfBridge(float dt, float dw, float dl, float dh, float dAlpha)
{
	//stub napred
	glPushMatrix();
		float dvaPremaJedanX = -((dl / 2) + ((1.5 * dl) / 3));
		float dvaPremaJedanY = ((dh / 3) / 2);
		glTranslatef(dvaPremaJedanX, dvaPremaJedanY, (dw / 2) + (dt / 2));
		DrawPrism(dt, dh, dt);
	glPopMatrix();

	//stub nazad
	glPushMatrix();
		glTranslatef(dvaPremaJedanX, dvaPremaJedanY, -((dw / 2) + (dt / 2)));
		DrawPrism(dt, dh, dt);
	glPopMatrix();

	//leva ploca
	glPushMatrix();
		glTranslatef(-((dl /2) + ((1.5 *dl) / 2)), 0.0, 0.0);
		DrawPrism(1.5*dl, dt, dw);
	glPopMatrix();

	//centralna ploca
	glPushMatrix();		
		glRotatef(dAlpha, 0.0, 0.0, 1.0);		
		DrawPrism(dl, dt, dw);
	glPopMatrix();

	//desna ploca
	glPushMatrix();
		glTranslatef(dl, 0.0, 0.0);
		glRotatef(-dAlpha, 0.0, 0.0, 1.0);
		DrawPrism(dl, dt, dw);
	glPopMatrix();

	//spoj napred
	glPushMatrix();
		glColor3f(0.0, 0.5, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);			
			glVertex3f(dvaPremaJedanX, (2 * (dh/3)), (dw/2 + dt/2));
			glVertex3f(dl / 2, 0.0, dw / 2);
		glEnd();
	glPopMatrix();

	//spoj nazad
	glPushMatrix();
		glColor3f(0.0, 0.5, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
			glVertex3f(dvaPremaJedanX, (2 * (dh / 3)), -(dw/2  + dt/2));
			glVertex3f(dl / 2, 0.0, -dw / 2);
		glEnd();
	glPopMatrix();
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
