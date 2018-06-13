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
	glEnable(GL_LIGHTING);
		
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
	gluLookAt(1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	//draw...
	//svetlo
	SetLight(5.0, 5.0, 0.0, -1.0, -1.0, 0.0);
	
	//materijal
	SetMaterial(0.4,0.5,0.4);
	
	//tekstura
	tex->PrepareTexture(true);
	tex->Select();

	DrawFigure(3.0, 0.25, 0.5, 0.1, 45, NULL, NULL);
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

void CGLRenderer::DrawPrism(float x, float y, float z)
{
	glBegin(GL_QUADS);	

	//napred
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(-x / 2, -y / 2, z / 2);//0
	glTexCoord2f(1 / 4, 0);
	glVertex3f(x / 2, -y / 2, z / 2);//1
	glTexCoord2f(1 / 4, 1);
	glVertex3f(x / 2, y / 2, z / 2);//2
	glTexCoord2f(0, 1);
	glVertex3f(-x / 2, y / 2, z / 2);//3

	//desno
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1 / 4, 0);
	glVertex3f(x / 2, -y / 2, z / 2);//1
	glTexCoord2f(2 / 4, 0);
	glVertex3f(x / 2, -y / 2, -z / 2);//5
	glTexCoord2f(2 / 4, 1);
	glVertex3f(x / 2, y / 2, -z / 2);//6
	glTexCoord2f(1 / 4, 1);
	glVertex3f(x / 2, y / 2, z / 2);//2

	//nazad
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(2 / 4, 0);
	glVertex3f(x / 2, -y / 2, -z / 2);//5
	glTexCoord2f(3 / 4, 0);
	glVertex3f(-x / 2, -y / 2, -z / 2);//4			
	glTexCoord2f(3 / 4, 1);
	glVertex3f(-x / 2, y / 2, -z / 2);//7
	glTexCoord2f(2 / 4, 1);
	glVertex3f(x / 2, y / 2, -z / 2);//6
	
	//levo
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(3 / 4, 0);
	glVertex3f(-x / 2, -y / 2, -z / 2);//4		
	glTexCoord2f(1, 0);
	glVertex3f(-x / 2, -y / 2, z / 2);//0
	glTexCoord2f(1, 1);
	glVertex3f(-x / 2, y / 2, z / 2);//3
	glTexCoord2f(3 / 4, 1);
	glVertex3f(-x / 2, y / 2, -z / 2);//7

	//gore
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-x / 2, y / 2, z / 2);//3
	glVertex3f(x / 2, y / 2, z / 2);//2
	glVertex3f(x / 2, y / 2, -z / 2);//6
	glVertex3f(-x / 2, y / 2, -z / 2);//7
	
	//dole
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-x / 2, -y / 2, z / 2);//0
	glVertex3f(x / 2, -y / 2, z / 2);//1
	glVertex3f(x / 2, -y / 2, -z / 2);//5
	glVertex3f(-x / 2, -y / 2, -z / 2);//4

	glEnd();
}

void CGLRenderer::SetMaterial(float r, float g, float b)
{
	float ambient[] = { 2*r, 2*g, 2*b, 1.0};
	float diffuse[] = { r, g, b, 1.0 };	
	float shininess = 15;
	float specular[] = { 255,255,255,1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
}

void CGLRenderer::SetLight(float x, float y, float z, float dx, float dy, float dz)
{
	float ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	float diffuse[] = { 1.0 , 1.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.5);

	float position[] = { x, y, z ,1.0 };
	float direction[] = { dx, dy, dz };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

	glEnable(GL_LIGHT0);
}

void CGLRenderer::DrawFigure(float length, float base, float height, float offset, float angle, COLORREF arColors[], CString arTextures[])
{
	//levi stub
	glPushMatrix();
		float moveX1 = -(length / 2) + offset + base / 2;
		float moveY1 = -(base / 2) - (height / 2);
		glTranslatef(moveX1, moveY1, 0.0);
		DrawPrism(base, height, base);
	glPopMatrix();

	//desni stub
	glPushMatrix();
		float moveX2 = (length / 2) - offset - base / 2;
		float moveY2 = -(base / 2) - (height / 2);
		glTranslatef(moveX2, moveY2, 0.0);
		DrawPrism(base, height, base);
	glPopMatrix();

	glRotatef(-angle, 0.0, 0.0, 1.0);

	//precka
	DrawPrism(length, base, base);	

	//teg
	glPushMatrix();
		float moveX3 = (length / 2) + base;
		glTranslatef(moveX3, 0.0, 0.0);
		DrawPrism(2*base,2*base,2*base);
	glPopMatrix();

	//konopac
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, - (base / 2), 0.0);
		glVertex3f(0.0, -(base / 2) - base, 0.0);
	glEnd();

	//znak stop
	glPushMatrix();
		float moveY4 = -(base / 2) - base - (base / 2);
		glTranslatef(0.0,moveY4,0.0);
		DrawPrism(base, base, 0.1*base);
	glPopMatrix();
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
