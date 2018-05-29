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
    PIXELFORMATDESCRIPTOR pfd ;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1; 
    pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
    pfd.iPixelType = PFD_TYPE_RGBA; 
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24; 
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
    
    if (nPixelFormat == 0) return false; 

    BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
    
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

	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	tex->LoadTexture((CString)"brick.png");
	
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
	
	tex->PrepareTexture(false);
	tex->Select();

	float a = 2.0;
	glBegin(GL_QUADS);
	
	//napred
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(a / 2, a / 2, a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-a / 2, a / 2, a / 2);
	
	//desno
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(a / 2, a / 2, -a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(a / 2, a / 2, a / 2);

	//iza
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(a / 2, a / 2, -a / 2);

	//levo
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-a / 2, a / 2, a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-a / 2, a / 2, -a / 2);

	//gore
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-a / 2, a / 2, a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(a / 2, a / 2, a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(a / 2, a / 2, -a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-a / 2, a / 2, -a / 2);

	//dole
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(a / 2, -a / 2, a / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-a / 2, -a / 2, -a / 2);

	glEnd();

	//----
	glFlush();
	SwapBuffers(pDC->m_hDC);
    //---------------------------------	
    wglMakeCurrent(NULL, NULL);
}

float CGLRenderer::toRad(float angle)
{
	return (angle * M_PI) / 180;
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

void CGLRenderer::DestroyScene(CDC *pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    // ... 
    wglMakeCurrent(NULL,NULL); 
    if(m_hrc) 
    {
        wglDeleteContext(m_hrc);
        m_hrc = NULL;
    }
}

void CGLRenderer::DrawAxes(float size)
{
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, size, 0.0);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, size);

	glEnd();
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
    do{
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
