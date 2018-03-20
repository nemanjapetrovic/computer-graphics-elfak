#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")


float vert[24];

CGLRenderer::CGLRenderer(void)
{
}

CGLRenderer::~CGLRenderer(void)
{
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

	glLineWidth(1.0);

	PrepareCube(1.0);

	//---------------------------------
    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    //---------------------------------
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(-7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	DrawRobot();

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
	float aspect = (double)w / (double)h;
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

void CGLRenderer::PrepareCube(float a)
{
	vert[0] = -a / 2; vert[1] = -a / 2; vert[2] = a / 2; //0
	vert[3] = a / 2; vert[4] = -a / 2; vert[5] = a / 2; //1
	vert[6] = a / 2; vert[7] = a / 2; vert[8] = a / 2;//2
	vert[9] = -a / 2; vert[10] = a / 2; vert[11] = a / 2;//3
	vert[12] = a / 2; vert[13] = -a / 2; vert[14] = -a / 2;//4
	vert[15] = a / 2; vert[16] = a / 2; vert[17] = -a / 2;//5
	vert[18] = -a / 2; vert[19] = a / 2; vert[20] = -a / 2;//6
	vert[21] = -a / 2; vert[22] = -a / 2; vert[23] = -a / 2;//7
}

void CGLRenderer::DrawCube()
{
	glVertexPointer(3, GL_FLOAT, 0, vert);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);

	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);

	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(5);
	glArrayElement(4);

	glArrayElement(4);
	glArrayElement(5);
	glArrayElement(6);
	glArrayElement(7);

	glArrayElement(6);
	glArrayElement(3);
	glArrayElement(0);
	glArrayElement(7);

	glArrayElement(3);
	glArrayElement(2);
	glArrayElement(5);
	glArrayElement(6);

	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(4);
	glArrayElement(7); 

	glEnd();	

	glDisableClientState(GL_VERTEX_ARRAY);

	DrawAxes(2.0);
}

void CGLRenderer::DrawRobot()
{
	glPushMatrix();
	
		//telo
		//glRotatef(-35.0, 1.0, 0.0, 0.0);
		glPushMatrix();
			glScaled(2.0, 2.0, 1.0);
			DrawCube();
		glPopMatrix();		

		//desna ruka nadlaktica
		glPushMatrix();			
			glTranslatef(1.5, 0.5, 0.0);			
			glRotatef(-40.0, 1.0, 0.0, 0.0);
			DrawCube();			

			//desna ruka podlaktica						
			glTranslatef(0.0, -1.0, 0.0);
			glRotatef(-20.0, 1.0, 0.0, 0.0);
			DrawCube();			
		glPopMatrix();

		//leva ruka nadlaktica
		glPushMatrix();
			glTranslatef(-1.5, 0.5, 0.0);
			glRotatef(-15.0, 1.0, 0.0, 0.0);
			DrawCube();
			
			//leva ruka podlaktica
			glTranslatef(0.0, -1.0, 0.0);
			glRotatef(-20.0, 1.0, 0.0, 0.0);
			DrawCube();
		glPopMatrix();


		//glava
		glRotatef(40.0, 0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(0.0, 1.5, 0.0);
			DrawCube();
		glPopMatrix();

	glPopMatrix();
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
