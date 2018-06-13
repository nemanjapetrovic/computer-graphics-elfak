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
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	//draw..	
	DrawScene(0.95 / 2, 0.4 / 2, 0.5 / 2, 0.5 / 2);	
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

void CGLRenderer::DrawTrapezoid(float a, float b, float h, float H)
{
	float naspramna = (a - b) / 2;
	float nalegla = h;
	float ugao = atan(naspramna / nalegla); //ugao u radijanima (cos,sin traze radijane)

	glBegin(GL_QUADS);

		//prednja
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-(a / 2), -(h / 2), H / 2);
		glVertex3f((a / 2), -(h / 2), H / 2);
		glVertex3f((b / 2), (h / 2), H / 2);
		glVertex3f(-(b / 2), (h / 2), H / 2);

		//desna
		glNormal3f(cos(ugao), 0.0, sin(ugao));
		glVertex3f((a / 2), -(h / 2), H / 2);
		glVertex3f((a / 2), -(h / 2), -(H / 2));
		glVertex3f((b / 2), (h / 2), -(H / 2));
		glVertex3f((b / 2), (h / 2), (H / 2));

		//nazad
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-(a / 2), -(h / 2), -(H / 2));
		glVertex3f((a / 2), -(h / 2), -(H / 2));
		glVertex3f((b / 2), (h / 2), -(H / 2));
		glVertex3f(-(b / 2), (h / 2), -(H / 2));

		//levo
		glNormal3f(cos(ugao), 0.0, sin(ugao));
		glVertex3f(-(a / 2), -(h / 2), -(H / 2));
		glVertex3f(-(a / 2), -(h / 2), H / 2);
		glVertex3f(-(b / 2), (h / 2), H / 2);
		glVertex3f(-(b / 2), (h / 2), -(H / 2));

		//gore
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-(b / 2), h / 2, H / 2);
		glVertex3f(b / 2, h / 2, H / 2);
		glVertex3f(b / 2, h / 2, -(H / 2));
		glVertex3f(-(b / 2), h / 2, -(H / 2));

		//dole
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-(a / 2), -(h / 2), H / 2);
		glVertex3f(a / 2, -(h / 2), H / 2);
		glVertex3f(a / 2, -(h / 2), -(H / 2));
		glVertex3f(-(a / 2), -(h / 2), -(H / 2));

	glEnd();
}

void CGLRenderer::DrawRing(float a, float b, float h, float H)
{
	// sluzi nam da odredimo rastojanje od centra za koje cemo da pomerimo svaki trapez
	float hipotenuza = sqrt(pow(h, 2) + pow(((a - b) / 2), 2));

	//za rotaciju
	float angle = 360 / 6;
	// pocecemo rotaciju od 12h na satu u pravcu suprotno od kazaljke na satu
	float tmpAngle = 90.0;
	for (int i = 0; i < 6; i++) 
	{		
		glPushMatrix();										
			
			// rotiraj u krug i prosledi ga na neko mesto
			glRotatef(tmpAngle, 0.0, 0.0, 1.0);
			glTranslatef(hipotenuza, 0.0, 0.0);

			// rotiraj inicijalno za 90 stpeeni da bi kasnije posle pomeranja gledao ka centru			
			glRotatef(90.0, 0.0, 0.0, 1.0);

			DrawTrapezoid(a, b, h, H);
		glPopMatrix();
		tmpAngle += angle;
	}
}

void CGLRenderer::SetMaterial(COLORREF clr)
{
	float r = GetRValue(clr);
	float g = GetGValue(clr);
	float b = GetBValue(clr);
	float ambient[] = { r/2, g/2, b/2, 1.0 };
	float diffuse[] = { r, g, b, 1.0 };
	float shinnines = 128.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinnines);
}

void CGLRenderer::DrawScene(float a, float b, float h, float H)
{
	float hipotenuza = sqrt(pow(h, 2) + pow(((a - b) / 2), 2));
	
	//centralni
	SetMaterial(RGB(0.7, 0.7, 0.7));
	DrawRing(a, b, h, H);

	//dole CYAN
	SetMaterial(RGB(0, 1, 1));
	glPushMatrix();
		float doleY = hipotenuza + h + h;
		glTranslatef(0.0, -doleY, 0.0);
		DrawRing(a, b, h, H);
	glPopMatrix();

	//gore CRVENO RGB
	SetMaterial(RGB(1.0, 0.0, 0.0));
	glPushMatrix();
		float goreY = hipotenuza + h + h;
		glTranslatef(0.0, goreY, 0.0);
		DrawRing(a, b, h, H);
	glPopMatrix();

	float x = hipotenuza + hipotenuza + (h / 2);
	float y = hipotenuza + (h / 2);
	
	//desno dole PLAVO RGB
	SetMaterial(RGB(0, 0, 1));
	glPushMatrix();
		glTranslatef(x, -y, 0.0);
		DrawRing(a, b, h, H);
	glPopMatrix();

	//levo dole ZELENO RGB
	SetMaterial(RGB(0.0,0.5,0.0));
	glPushMatrix();
		glTranslatef(-x, -y, 0.0);
		DrawRing(a, b, h, H);
	glPopMatrix();

	//desno gore PURPLE
	SetMaterial(RGB(1,0,1));
	glPushMatrix();
		glTranslatef(x, y, 0.0);
		DrawRing(a, b, h, H);
	glPopMatrix();

	//levo gore YELLOW
	SetMaterial(RGB(1, 1, 0));
	glPushMatrix();
		glTranslatef(-x, y, 0.0);
		DrawRing(a, b, h, H);
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
