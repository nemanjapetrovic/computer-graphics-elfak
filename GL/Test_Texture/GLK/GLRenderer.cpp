#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
#include "Tex.h"
//#pragma comment(lib, "GL\\glut32.lib")


float vert[72];
float tex[48];

CTex *brick_tex;

CGLRenderer::CGLRenderer(void)
{
	brick_tex = new CTex();
}

CGLRenderer::~CGLRenderer(void)
{
	brick_tex->Release();
	delete brick_tex;
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
	
	PrepareCube(1.0);	

	brick_tex->LoadTexture((CString)"brick.png");

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
	
	// Kocka obicna sa ciglama
	brick_tex->PrepareTexture(false);
	brick_tex->Select();
	DrawBrickCube();

	// zid iza kocke
	glPushMatrix();
		glTranslatef(0.0, 0.0, -2.5);
		DrawWall(5.0, 5.0, 1.0, 1.0);
	glPopMatrix();

	// levi zid
	glPushMatrix();
		glTranslatef(-2.5, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		DrawWall(5.0, 5.0, 1.0, 1.0);
	glPopMatrix();

	// pod
	glPushMatrix();
		glTranslatef(0.0, -2.5, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);		
		DrawWall(5.0, 5.0, 1.0, 1.0);
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
	//napred
	vert[0] = -a / 2; vert[1] = -a / 2; vert[2] = a / 2; //0
	vert[3] = a / 2; vert[4] = -a / 2; vert[5] = a / 2; //1
	vert[6] = a / 2; vert[7] = a / 2; vert[8] = a / 2;//2
	vert[9] = -a / 2; vert[10] = a / 2; vert[11] = a / 2;//3

	//desno
	vert[12] = a / 2; vert[13] = -a / 2; vert[14] = a / 2; //1
	vert[15] = a / 2; vert[16] = a / 2; vert[17] = a / 2;//2
	vert[18] = a / 2; vert[19] = a / 2; vert[20] = -a / 2;//5
	vert[21] = a / 2; vert[22] = -a / 2; vert[23] = -a / 2;//4

	//iza
	vert[24] = a / 2; vert[25] = a / 2; vert[26] = -a / 2;//5
	vert[27] = a / 2; vert[28] = -a / 2; vert[29] = -a / 2;//4
	vert[30] = -a / 2; vert[31] = -a / 2; vert[32] = -a / 2;//7	
	vert[33] = -a / 2; vert[34] = a / 2; vert[35] = -a / 2;//6
	
	//levo
	vert[36] = -a / 2; vert[37] = -a / 2; vert[38] = -a / 2;//7	
	vert[39] = -a / 2; vert[40] = a / 2; vert[41] = -a / 2;//6
	vert[42] = -a / 2; vert[43] = a / 2; vert[44] = a / 2;//3
	vert[45] = -a / 2; vert[46] = -a / 2; vert[47] = a / 2; //0

	//gore
	vert[48] = -a / 2; vert[49] = a / 2; vert[50] = a / 2;//3
	vert[51] = a / 2; vert[52] = a / 2; vert[53] = a / 2;//2
	vert[54] = a / 2; vert[55] = a / 2; vert[56] = -a / 2;//5
	vert[57] = -a / 2; vert[58] = a / 2; vert[59] = -a / 2;//6

	//dole
	vert[60] = -a / 2; vert[61] = -a / 2; vert[62] = a / 2; //0
	vert[63] = a / 2; vert[64] = -a / 2; vert[65] = a / 2; //1
	vert[66] = a / 2; vert[67] = -a / 2; vert[68] = -a / 2;//4	
	vert[69] = -a / 2; vert[70] = -a / 2; vert[71] = -a / 2;//7	


	//texture

	//napred
	tex[0] = 0.0 ; tex[1] = 0.0;//0
	tex[2] = 1.0;  tex[3] = 0.0;//1
	tex[4] = 1.0; tex[5] = 1.0;//2
	tex[6] = 0.0; tex[7] = 1.0;//3

	//desno
	tex[8] = 0.0; tex[9] = 0.0;//1
	tex[10] = 0.0; tex[11] = 1.0;//2
	tex[12] = 1.1; tex[13] = 1.1;//5
	tex[14] = 1.0; tex[15] = 0.0;//4
	
	//iza
	tex[16] = 0.0; tex[17] = 1.0;//5
	tex[18] = 0.0; tex[19] = 0.0;//4
	tex[20] = 1.0; tex[21] = 0.0;//7
	tex[22] = 1.0; tex[23] = 1.1;//6

	//levo
	tex[24] = 0.0; tex[25] = 0.0;//7
	tex[26] = 0.0; tex[27] = 1.0;//6
	tex[28] = 1.0; tex[29] = 1.0;//3
	tex[30] = 1.0; tex[31] = 0.0;//0

	//gore
	tex[32] = 0.0; tex[33] = 0.0;//3
	tex[34] = 1.0; tex[35] = 0.0;//2												
	tex[36] = 1.1; tex[37] = 1.1;//5
	tex[38] = 0.0; tex[39] = 1.0;//6
	
	//dole
	tex[40] = 0.0; tex[41] = 0.0;//0
	tex[42] = 1.0; tex[43] = 0.0;//1
	tex[44] = 1.1; tex[45] = 1.1;//4
	tex[46] = 0.0; tex[47] = 1.0;//7

}

void CGLRenderer::DrawWall(double sizeX,double sizeY, int repX, int repY)
{
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex3f((-sizeX / 2), (-sizeY / 2), 0.0);

	glTexCoord2f(repX, 0.0);
	glVertex3f((sizeX / 2), (-sizeY / 2), 0.0);

	glTexCoord2f(repX, repY);
	glVertex3f((sizeX / 2), (sizeY / 2), 0.0);

	glTexCoord2f(0.0, repY);
	glVertex3f((-sizeX / 2), (sizeY / 2), 0.0);

	glEnd();
}

void CGLRenderer::DrawBrickCube()
{
	DrawAxes(2.0);
	
	glVertexPointer(3, GL_FLOAT, 0, vert);	
	glTexCoordPointer(2, GL_FLOAT, 0, tex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
