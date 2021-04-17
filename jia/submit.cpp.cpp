/*****************************************************************************
FILE : submit.c (Assignment 1)
NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
Student Information
Student ID:021830122
Student Name:
*****************************************************************************/

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include<Windows.h>

const GLdouble FRUSTDIM = 100.0f;


static GLuint texName;  //texture object
static GLuint texName1;
static GLuint texName2;
static GLuint texName3;
/* Initialize material properties */
GLfloat mat_ambient[] = { 0.931250, 0.231250, 0.231250, 1 };
GLfloat mat_diffuse[] = { 0.277500, 0.277500, 0.277500, 1 };
GLfloat mat_specular[] = { 0.773911, 0.773911, 0.773911, 1 };
GLfloat mat_shininess[] = { 89.599998 };
const GLfloat PI = 3.141592653f;
GLubyte  Tv_Color[][3] = { {0,0,0} ,{0,0,255} };
GLint Tv_Color_Choice = 0;


GLfloat arm = 20.0;
GLfloat xiaom = 130.0;   //xiaom  y  position
GLfloat xiaomx = 300;    //xiaom  x  position
GLfloat lookx = 300.0;     //the location where we look at
GLfloat looky = -30.0;
GLfloat lookz = -400.0;
GLfloat personangle = 0;
GLfloat up_down_angle = 0;

GLfloat doorangle_1 = 0;

GLfloat drawerposition1 = -20;
GLfloat drawerposition2 = -20;
GLfloat drawerposition3 = -20;

GLfloat chairposition = 0;

GLfloat teapotpositionx = 0;
GLfloat teapotpositiony = 0;
GLfloat teapotrotatef = 0;

GLfloat basket_x = 0;
GLfloat basket_y = 0;
GLfloat basket_dirx = 1;
GLfloat basket_diry = 1;
//

float h = 0.0f;
float m = 0.0f;
float s = 0.0f;


GLfloat legangle = 0;
/* lighting mat */

//light 0
GLfloat light0_pos[] = { 0.0f, 1.f, -1.f, 0.0f };
GLfloat light0_amb[] = { 0.6, 0.6, 0.6, 1.0f };
GLfloat light0_diff[] = { 0.5, 0.5, 0.5, 0.3 };

//light1
GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_speculer[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { 0.0f, 1.f, -1.f, 0.0f };
GLfloat spot_direction[] = { -1.0, 0, 0 };


/* animation */
GLUquadricObj *obj;

#define WIDTH 64
#define HEIGHT 64
GLubyte Image[WIDTH][HEIGHT][4];   //texture picture
GLubyte Image1[WIDTH][HEIGHT][4];
GLubyte Image2[WIDTH][HEIGHT][4];
GLubyte Image3[WIDTH][HEIGHT][4];


/* 镜头漫游*/
struct Eyepoint
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Eye;


/* 窗口 */
GLint WinWidth, WinHeight;

/* 动画参数 */
GLfloat
FanAngle = 0,
TeapotPos = -96,
PostPos = -100,
HolePos = -100,
StoolPos = 50,
Sphereangle = 0,
SphereScale = 6;


//switches
bool Teapot_dire = true, Stool_dir = true;

bool run_go = 0;

enum { door1_off, door1_on } Door1;


enum { chair_off, chair_on } Chair;

enum { light_on, light_off } Light;

enum { run_on, run_off } run;

enum { teapotstop, teapot_translate } Teapot;

enum { postempty, post_up, post_down } Post;

enum { stoolstop, stoolmove } Stool;

enum { sphere_stop, sphere_rotate } Sphere;

enum { sphere_large, sphere_small } Sphere1;

enum { fan_turnoff, fan_turnon } Fan;

enum { closehole, openhole } Hole;

enum { teapot_off, teapot_on }Teapot1;

enum { draw1_off, draw1_on } Draw1;

enum { draw2_off, draw2_on } Draw2;

enum { draw3_off, draw3_on } Draw3;

enum { basket_off, basket_on } Basket;

enum { basketback_off, basketback_on }Basketback;

enum { basketfloor_off, basketfloor_on }Basketfloor;

void MakeImage3(void) // texture of clothe
{
	int i, j, c;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{


			c = (((i & 0x5) == 0) ^ ((j & 0x5) == 0)) * 255;
			//计算纹理颜色

			if (c == 255)
			{
				Image3[i][j][0] = 245;
				Image3[i][j][1] = 245;
				Image3[i][j][2] = 245;
				Image3[i][j][3] = 255;
			}
			else {
				Image3[i][j][0] = 128;
				Image3[i][j][1] = 128;
				Image3[i][j][2] = 128;
				Image3[i][j][3] = 255;
			}





		}
	}

}
void MakeImage2(void)  //texture of  air conditioner
{
	int i, j, c;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			//c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			////计算纹理颜色
			if (i >= HEIGHT / 4 && i <= HEIGHT / 3 && j >= 4.5* WIDTH / 12 && j <= 8.5* WIDTH / 12)
			{
				Image2[i][j][0] = 60;
				Image2[i][j][1] = 60;
				Image2[i][j][2] = 60;
				Image2[i][j][3] = 255;
			}
			else if (i % 2 && i <= HEIGHT / 5 && (j >= WIDTH / 12 && j <= 11 * WIDTH / 12))
			{

				Image2[i][j][0] = 245;
				Image2[i][j][1] = 245;
				Image2[i][j][2] = 245;
				Image2[i][j][3] = 255;
			}
			else if (i <= HEIGHT / 5 && (j >= WIDTH / 12 && j <= 11 * WIDTH / 12))
			{

				Image2[i][j][0] = 0;
				Image2[i][j][1] = 0;
				Image2[i][j][2] = 0;
				Image2[i][j][3] = 255;

			}
			else {
				Image2[i][j][0] = 245;
				Image2[i][j][1] = 245;
				Image2[i][j][2] = 245;
				Image2[i][j][3] = 255;
			}


		}
	}
}
void MakeImage1(void)//texture of ceil 
{
	int i, j, c;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{

			if (Light == light_on)
			{
				if (i % 6 || j % 6)
				{

					Image1[i][j][0] = 225;
					Image1[i][j][1] = 218;
					Image1[i][j][2] = 190;
					Image1[i][j][3] = 255;
				}
				else
				{

					Image1[i][j][0] = 255;
					Image1[i][j][1] = 255;
					Image1[i][j][2] = 255;
					Image1[i][j][3] = 255;

				}
			}
			else {
				Image1[i][j][0] = 0;
				Image1[i][j][1] = 0;
				Image1[i][j][2] = 0;
				Image1[i][j][3] = 255;
			}


		}
	}
	glFlush();
}
void MakeImage(void)//texture picture of floor 
{
	int i, j, c;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			c = (((i & 0x5) == 0) ^ ((j & 0x5) == 0)) * 255;
			if (c != 255)
			{
				Image[i][j][0] = 225;
				Image[i][j][1] = 218;
				Image[i][j][2] = 190;
				Image[i][j][3] = 255;
			}
			else {
				Image[i][j][0] = 235;
				Image[i][j][1] = 235;
				Image[i][j][2] = 235;
				Image[i][j][3] = 255;
			}


		}
	}
}
void Initialization3(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//设置两点间颜色平滑过滤
	glEnable(GL_DEPTH_TEST);

	MakeImage3();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glGenTextures(1, &texName3);//创建1个纹理对象，&texName指向纹理索引
	glBindTexture(GL_TEXTURE_2D, texName3);//绑定纹理：改变OpenGL状态，使得后续的纹理操作都对texName指向的2D纹理生效

	//设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,   //  第二个参数:指定详细程度编号。级别0是基本图像级别。级别n是第n个缩略图缩小图像
		0, GL_RGBA, GL_UNSIGNED_BYTE, Image3);

}
void Initialization2(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//设置两点间颜色平滑过滤
	glEnable(GL_DEPTH_TEST);
	MakeImage2();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName2);//创建1个纹理对象，&texName指向纹理索引
	glBindTexture(GL_TEXTURE_2D, texName2);//绑定纹理：改变OpenGL状态，使得后续的纹理操作都对texName指向的2D纹理生效
	//设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,   //  第二个参数:指定详细程度编号。级别0是基本图像级别。级别n是第n个缩略图缩小图像
		0, GL_RGBA, GL_UNSIGNED_BYTE, Image2);


}
void Initialization(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//设置两点间颜色平滑过滤
	glEnable(GL_DEPTH_TEST);
	MakeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);//创建1个纹理对象，&texName指向纹理索引
	glBindTexture(GL_TEXTURE_2D, texName);//绑定纹理：改变OpenGL状态，使得后续的纹理操作都对texName指向的2D纹理生效
	//设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,   //  第二个参数:指定详细程度编号。级别0是基本图像级别。级别n是第n个缩略图缩小图像
		0, GL_RGBA, GL_UNSIGNED_BYTE, Image);
}
void Initialization1(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//设置两点间颜色平滑过滤
	glEnable(GL_DEPTH_TEST);

	MakeImage1();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glGenTextures(1, &texName1);//创建1个纹理对象，&texName指向纹理索引
	glBindTexture(GL_TEXTURE_2D, texName1);//绑定纹理：改变OpenGL状态，使得后续的纹理操作都对texName指向的2D纹理生效

	//设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,   //  第二个参数:指定详细程度编号。级别0是基本图像级别。级别n是第n个缩略图缩小图像
		0, GL_RGBA, GL_UNSIGNED_BYTE, Image1);

}
void onDisplay2()//air conditioner
{
	if (Light == light_on)  //  
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texName2);
		glTranslatef(65, -50, -190);
		glRotatef(-7, 0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(24, 80, 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(24, -80, 10);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-24, -80, 10);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-24, 80, 10);
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(40, 80, -10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(40, -80, -10);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-40, -80, -10);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-40, 80, -10);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);   //ar right side 
		glColor3ub(225, 225, 225);
		glVertex3f(24, 80, 10);
		glVertex3f(40, 80, -10);
		glVertex3f(40, -80, -10);
		glVertex3f(24, -80, 10);
		glEnd();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(65, -50, -190);
		glRotatef(-7, 0, 1, 0);
		glBegin(GL_QUADS);
		glColor3ub(225, 225, 225);
		glVertex3f(24, 60, 10);
		glVertex3f(24, -80, 10);
		glVertex3f(-24, -80, 10);
		glVertex3f(-24, 60, 10);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(40, 80, -10);
		glVertex3f(40, -80, -10);
		glVertex3f(-40, -80, -10);
		glVertex3f(-40, 80, -10);
		glEnd();

		glBegin(GL_QUADS);   //ar right side 
		glColor3ub(225, 225, 225);
		glVertex3f(24, 80, 10);
		glVertex3f(40, 80, -10);
		glVertex3f(40, -80, -10);
		glVertex3f(24, -80, 10);
		glEnd();

		glBegin(GL_QUADS);   //ar right side 
		glColor3ub(100, 100, 100);
		glVertex3f(22, 80, 12);
		glVertex3f(22, 45, 12);
		glVertex3f(-22, 45, 12);
		glVertex3f(-22, 80, 12);
		glEnd();


		glPopMatrix();
	}



}
void OnDisplay1(void)// ceil texture
{
	if (Light == light_on)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glBindTexture(GL_TEXTURE_2D, texName1);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, 100, -200);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-100, 100, -200);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, 100, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(100, 100, 0);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		glBegin(GL_QUADS);
		glVertex3f(100, 100, -200);
		glVertex3f(-100, 100, -200);
		glVertex3f(-100, 100, 0);
		glVertex3f(100, 100, 0);
		glEnd();
	}


}

void OnDisplay(void)   //floor  texture
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (Light == light_on)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texName);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, -100, -200);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-100, -100, -200);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, -100, 0);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(100, -100, 0);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		glBegin(GL_QUADS);
		glVertex3f(100, -100, -200);
		glVertex3f(-100, -100, -200);
		glVertex3f(-100, -100, 0);
		glVertex3f(100, -100, 0);
		glEnd();

	}


}



void init(void) // All Setup For OpenGL Goes Here
{

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);//光源中的环境光强度
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);//光源中的散射光强度
	//启用灯源
	glEnable(GL_LIGHTING);
	//启用0号光源(0-7)
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_speculer);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);

	glEnable(GL_LIGHT1);

	//深度测试，根据坐标远近自动隐藏遮住图形
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GLUT_MULTISAMPLE);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	Eye.x = 300.0f;
	Eye.y = -30.0f;
	Eye.z = 180.0f;

	obj = gluNewQuadric();
}



void timerFunc(int value) //count next time
{
	s += 1;
	int carry1 = 0;
	if (s >= 60)
	{
		s = 0;
		carry1 = 1;
	}
	m += carry1;
	int carry2 = 0;
	if (m >= 60)
	{
		m = 0;
		carry2 = 1;
	}
	h += carry2;
	if (h >= 24)
		h = 0;

	glutPostRedisplay(); // 重画

	glutTimerFunc(1000, timerFunc, 1); // 每一秒中执行一次
}

/*
初始化函数
设置背景，获取时间
*/
void SetupRC(void)       //get systerm time
{
	// 设置窗口为白色

	// 获取本地当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	h = sys.wHour;
	m = sys.wMinute;
	s = sys.wSecond;
}

void DrawDesk()
{
	glColor3ub(144, 238, 144);
	glPushMatrix();

	glTranslatef(-60, -60, -175);

	glPushMatrix();
	glTranslatef(40, 0, 12);
	glTranslatef(chairposition, 0, 0);
	glPushMatrix();
	glScalef(40, 5, 15);

	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();

	glColor3ub(176, 196, 222);
	glTranslatef(0, 5, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(4, 10, 31, 31);
	//gluCylinder(obj, 10, 10, 5, 31, 31);
	glPopMatrix();
	glColor3ub(144, 238, 144);
	for (int i = 1; i <= 4; i++)
	{
		glPushMatrix();
		glTranslatef(18, 5 + i * 10, 0);
		glScalef(3, 6, 15);
		glutSolidCube(1);
		glPopMatrix();
	}


	glPushMatrix();   //chair  right reg
	glTranslatef(18, -15, 6);
	glScalef(4, 125, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, -15, -6);
	glScalef(4, 125, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //chair left reg
	glTranslatef(-18, -15, 6);
	glScalef(4, 35, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18, -15, -6);
	glScalef(4, 35, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();   // desk 
	glTranslatef(0, 25, 0);
	glScalef(50, 6, 40);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //desk  regs 
	glTranslatef(23, -20, -20);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, 1, 0);
	glScalef(3, 3, 90);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, -20, 20);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, 1, 0);
	glScalef(3, 3, 90);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23, -20, 20);
	glRotatef(90, 1, 0, 0);
	glRotatef(-20, 0, 1, 0);
	glScalef(3, 3, 90);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-23, -20, -20);
	glRotatef(90, 1, 0, 0);
	glRotatef(-20, 0, 1, 0);
	glScalef(3, 3, 90);
	glutSolidCube(1);
	glPopMatrix();



	glPopMatrix();
}

void DrawSofa()
{
	glPushMatrix();

	glTranslatef(10, 0, -15);
	glTranslatef(-80, -95, -85);

	glPushMatrix();
	glScalef(55, 10, 40);                   //沙发下
	glutSolidCube(1);
	glPopMatrix();


	glTranslatef(0, 8, 0);                  //沙发上
	glColor3ub(128, 64, 0);
	glPushMatrix();
	glScalef(55, 7, 37);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	//沙发前的桌子

	glTranslatef(77, 0, 0);
	glColor3ub(150, 150, 150);
	glPushMatrix();
	glTranslatef(25, -5, 22.5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 5, 5, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, -5, -22.5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 5, 5, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, -5, 22.5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 4, 4, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, -5, -22.5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 4, 4, 13, 31, 31);
	glPopMatrix();

	glColor3ub(200, 200, 200);
	glTranslatef(0, 8, 0);


	glScalef(60, 10, 55);
	glutSolidCube(1);

	glPopMatrix();


	glPushMatrix();   //把手1

	glColor3ub(107, 142, 35);
	glTranslatef(0, 3, 20);
	glPushMatrix();
	glScalef(55, 13, 3);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();  //把手2
	glTranslatef(0, 3, -20);
	glPushMatrix();
	glScalef(55, 13, 3);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();


	glColor3ub(139, 139, 122);
	glTranslatef(-20, 18, 0);

	glPushMatrix();
	glScalef(10, 30, 40);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void DrawDoor()
{
	glPushMatrix();

	glColor3ub(255, 255, 250);
	glPushMatrix();
	glTranslatef(-35, 0, 0);
	glScalef(130, 200, 5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(65, 50, 0);
	glScalef(70, 100, 5);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3ub(0, 255, 255);
	glPushMatrix();
	glTranslatef(30, -50, 0);
	glRotatef(doorangle_1, 0, 1, 0);
	glTranslatef(35, 0, 0);
	glPushMatrix();

	glPushMatrix();

	glTranslatef(30, 8, 0);
	glColor3ub(233, 233, 233);
	gluCylinder(obj, 1.5, 1.5, 5, 31, 31);//

	glPushMatrix();
	glTranslatef(0, 0, 5);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(obj, 1.5, 1.5, 8, 31, 31);

	glPopMatrix();

	glPopMatrix();
	glTranslatef(0, 30, 5);

	glColor3ub(233, 233, 233);
	glutSolidSphere(1, 31, 31);
	glColor3ub(0, 255, 255);


	glPopMatrix();
	glScalef(70, 100, 5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();

}

void DrawTime()
{
	glPushMatrix();

	glColor3ub(128, 128, 128); // 黑色
	glPushMatrix();
	// 1 绘制外围同心圆
	int cx = 0; //中心点
	int cy = 70;
	int R = 14; // 半径长
	int n = 10130;
	int i;
	glBegin(GL_LINE_LOOP); // 绘制多边形，n足够大就会变成圆形
	for (i = 0; i < n; i++)
	{
		glVertex3f(cx + (R + 0.55)*cos(2 * PI / n * i), cy + (R + 0.55)*sin(2 * PI / n * i), -195);
	}
	glEnd();


	int lines = 60;
	float ship1 = 5;
	float ship2 = 3;
	for (i = 0; i < lines; i++)
	{
		if (i % 5 == 0)    //  0（12）-11的短线
		{
			glLineWidth(3);
			//glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(cx + (R + 0.5 - ship1)*cos(2 * PI / lines * i), cy + (R + 0.5 - ship1)*sin(2 * PI / lines * i), -195);
			glVertex3f(cx + (R + 0.5) * cos(2 * PI / lines * i), cy + (R + 0.5) * sin(2 * PI / lines * i), -195);
			glEnd();
		}
		else
		{
			glLineWidth(1.5);  //其他的刻度
			//glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(cx + ((R + 0.5) - ship2)*cos(2 * PI / lines * i), cy + ((R + 0.5) - ship2)*sin(2 * PI / lines * i), -195);
			glVertex3f(cx + (R + 0.5) * cos(2 * PI / lines * i), cy + (R + 0.5) * sin(2 * PI / lines * i), -195);
			glEnd();
		}
	}


	glBegin(GL_POLYGON);
	for (i = 0; i < n; ++i)
		glVertex3f(cx + 0.2 * cos(2 * PI / n * i), cy + 0.2 * sin(2 * PI / n * i), -195);
	glEnd();

	// 4 绘制时 分 秒针，三条直线，长短粗细不一样
	int h_len = R - 3 * ship1;
	int m_len = R - ship1;
	int s_len = R - ship1 + 2 * ship1;

	float s_Angle = s / 60.0;
	float m_Angle = (m * 60 + s) / 3600.0;
	float h2 = h >= 12 ? (h - 12) : h;
	float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

	glLineWidth(1); // 秒
	glBegin(GL_LINES);
	glVertex3f(cx - 2 * ship1 * sin(2 * PI*s_Angle), cy - 2 * ship1*cos(2 * PI*s_Angle), -195);
	glVertex3f(cx + (R - ship2)*sin(2 * PI*s_Angle), cy + (R - ship2)*cos(2 * PI*s_Angle), -195);
	glEnd();

	glLineWidth(3); // 时
	glBegin(GL_LINES);
	glVertex3f(cx, cy, -195);
	glVertex3f(cx + (h_len + 5) * sin(2 * PI*h_Angle), cy + (h_len + 5) * cos(2 * PI*h_Angle), -195);
	glEnd();

	glLineWidth(2); // 分
	glBegin(GL_LINES);
	glVertex3f(cx, cy, -195);
	glVertex3f(cx + m_len * sin(2 * PI*m_Angle), cy + m_len * cos(2 * PI*m_Angle), -195);
	glEnd();

	glPopMatrix();

	glPopMatrix();
}
void DrawWalls()
{
	/*  room space
		x:100 ~ -100
		y:100 ~ -100
		z:0 ~ -200
	*/
	glPushMatrix();
	//back wall 
	glBegin(GL_QUADS);
	glColor3ub(235, 235, 235);
	glVertex3f(-100, -100, -200);
	glVertex3f(100, -100, -200);

	glVertex3f(100, 100, -200);
	glVertex3f(-100, 100, -200);
	glEnd();

	//left wall
	glBegin(GL_QUADS);   //floor  plus
	glVertex3f(1000, -101, -200);
	glVertex3f(-1000, -101, -200);
	glVertex3f(-1000, -101, 200);
	glVertex3f(1000, -101, 200);
	glEnd();

	glColor3ub(138, 138, 138);
	glBegin(GL_QUADS);   //back plus
	glVertex3f(-1000, -101, -200);
	glVertex3f(1000, -101, -200);

	glVertex3f(1000, 100, -200);
	glVertex3f(-1000, 100, -200);
	glEnd();

	glColor3ub(174, 174, 174);
	glBegin(GL_QUADS);  //ceil plus
	glVertex3f(-1000, 101, -200);
	glVertex3f(-1000, 101, 200);

	glVertex3f(1000, 101, 200);
	glVertex3f(1000, 101, -200);
	glEnd();

	//left wall
	glBegin(GL_QUADS);
	glColor3ub(225, 218, 190);
	glVertex3f(-100, 100, -200);
	glVertex3f(-100, 100, 0);
	glVertex3f(-100, -100, 0);
	glVertex3f(-100, -100, -200);
	glEnd();
	//right wall
	glBegin(GL_QUADS);
	glVertex3f(100, 100, -200);
	glVertex3f(100, 100, 0);
	glVertex3f(100, -100, 0);
	glVertex3f(100, -100, -200);
	glEnd();
	//floor
	glPopMatrix();
	// xiaoming
	glPushMatrix();
	glTranslatef(xiaomx, -10.0, xiaom);		// 可设动画

	// arms
	glColor3f(0.9, 0.7, 0.6);
	glPushMatrix();
	glTranslatef(-12.5, -25.0, 0.0);

	glPushMatrix();

	glTranslatef(9, -20, 0);
	glColor3ub(236, 40, 31);
	glTranslatef(-20, -20, 0);

	glPushMatrix();
	glTranslatef(0, 5, 0);
	glTranslatef(basket_x*basket_dirx, -basket_y * basket_diry, 0);
	glutWireSphere(6.5, 31, 31);
	glPopMatrix();


	glPopMatrix();

	glColor3ub(128, 128, 128);

	glRotatef(arm + 11, 0.0, 0.0, -1.0);		// 可设动画
	glTranslatef(0.0, -15.0, 0.0);
	glScalef(5.0, 30.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(12.5, -25.0, 0.0);
	glRotatef(arm + 11, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -15.0, 0.0);
	glScalef(5.0, 30.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();
	// head
	glPushMatrix();

	glTranslatef(0.0, -10.0, 0.0);
	glRotatef(personangle, 0, 1, 0);

	glRotatef(up_down_angle, 1, 0, 0);
	glColor3f(0.9, 0.7, 0.6);
	glScalef(13.0, 12.0, 15.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -10.0, 0.0);

	// neck
	glColor3ub(132, 132, 132);
	glTranslatef(0.0, -10.0, 0.0);

	glScalef(8.0, 10.0, 10.0);
	glutSolidCube(1.0);

	// body
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.125, 0.1, 0.1);
	glTranslatef(0.0, -18.0, 0.0);


	if (Light == light_on)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texName3);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-12.5, -17.5, 7.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.5, 17.5, 7.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.5, 17.5, 7.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.5, -17.5, 7.5);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	glColor3ub(128, 128, 128);
	glScalef(25.0, 35.0, 15.0);
	glutSolidCube(1.0);

	// legs
	glPushMatrix();
	glColor3ub(128, 128, 128);
	glScalef(1.0 / 25.0, 1.0 / 35.0, 1.0 / 15.0);
	glTranslatef(-9.0, -15.0, 0.0);
	glRotatef(legangle, 1, 0, 0);
	glTranslatef(0.0, -20.0, 0.0);
	glScalef(7.0, 35.0, 15.0);
	glutSolidCube(1.0);

	glPushMatrix();

	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3ub(128, 128, 128);
	glScalef(1.0 / 25.0, 1.0 / 35.0, 1.0 / 15.0);
	glTranslatef(-9.0, -15.0, 0.0);
	glRotatef(-legangle, 1, 0, 0);
	glTranslatef(0.0, -20.0, 0.0);
	glScalef(7.0, 35.0, 15.0);
	//glutSolidCube(1.0);
	glScalef(1.0 / 7.0, 1.0 / 35.0, 1.0 / 15.0);
	glTranslatef(18.0, 0.0, 0.0);
	glScalef(7.0, 35.0, 15.0);
	glutSolidCube(1.0);

	glPopMatrix();
	glPopMatrix();

}

void Drawtable()   //TV
{
	glPushMatrix();

	glTranslatef(-6, 0, 60);
	//木板
	glColor3ub(139, 115, 85);
	glTranslatef(90, -92, -170);

	glPushMatrix();  //液晶电视
	glTranslatef(-1, 64, 0);

	glPushMatrix();


	glColor3ub(47, 79, 79);
	glScalef(7, 30, 40);
	glutSolidCube(1);

	glColor3ub(Tv_Color[Tv_Color_Choice][0], Tv_Color[Tv_Color_Choice][1], Tv_Color[Tv_Color_Choice][2]);
	glScalef(1.1, 0.9, 0.9);
	glutSolidCube(1);
	glPopMatrix();

	glColor3ub(47, 79, 79);


	glPushMatrix();
	glTranslatef(0, -14, -12);
	glRotatef(120, 1, 0, 0);
	gluCylinder(obj, 2, 2, 33, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -27, 12);
	glRotatef(-120, 1, 0, 0);
	gluCylinder(obj, 2, 2, 33, 31, 31);
	glPopMatrix();





	glPopMatrix();

	glPushMatrix();   //  第一个抽屉

	glTranslatef(drawerposition1 - 1, 32, 0);

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	glScalef(1.5, 14, 40);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-26, 0, 0);
	glScalef(2, 1, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -8, 0);
	glScalef(30, 1.5, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();  //


	glPushMatrix();   //  第二个抽屉

	glTranslatef(drawerposition2 - 1, 16, 0);

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	glScalef(1.5, 14, 40);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-26, 0, 0);
	glScalef(2, 1, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -8, 0);
	glScalef(30, 1.5, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();  //

	glPushMatrix();   //  第三个抽屉

	glTranslatef(drawerposition3 - 1, 0, 0);

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	glScalef(1.5, 14, 40);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-26, 0, 0);
	glScalef(2, 1, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -20);
	glScalef(30, 14, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -8, 0);
	glScalef(30, 1.5, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();  //


	glScalef(30, 16, 50);

	glPushMatrix();
	glScalef(1, 0.9, 0.9);
	glutSolidCube(1);

	glPopMatrix();

	glutSolidCube(1);

	glTranslatef(0, 1, 0);

	glColor3ub(139, 50, 85);

	glutSolidCube(1);
	glColor3ub(139, 115, 85);
	glTranslatef(0, 1, 0);
	glutSolidCube(1);



	glPopMatrix();


	//石柜
	glPushMatrix();
	glColor3ub(139, 139, 122);
	glTranslatef(90, 50, -115);
	glScalef(20, 1, 60);
	glutSolidCube(1);

	glTranslatef(0, -30, 0);
	glutSolidCube(1);

	glPopMatrix();

}



void DrawTeapot()
{
	glPushMatrix();

	glPushMatrix();
	glTranslatef(88, -55, -96);
	glTranslatef(-100, -12, 10);
	glTranslatef(0, 0, -15);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 2, 4, 8, 31, 31);


	glPopMatrix();
	//茶壶
	glColor3ub(139, 69, 19);
	glTranslatef(88, -55, TeapotPos);
	glTranslatef(-100, -12, 10);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, teapotpositiony, 0);
	glTranslatef(teapotpositionx, 0, 0);
	glRotatef(teapotrotatef, 0, 0, 1);
	glutSolidTeapot(7);
	glPopMatrix();

}

void DrawWindow()
{
	glPushMatrix();

	//窗户
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-99.9, 60, -110);
	glVertex3f(-99.9, 60, -85);
	glVertex3f(-99.9, 25, -85);
	glVertex3f(-99.9, 25, -110);
	glEnd();

	//栏杆
	glColor3ub(0, 255, 0);
	glLineWidth(5);

	for (int i = 0; i <= 4; i++)
	{
		if (i == 0 || i == 4 || i == 2)
		{
			glLineWidth(11);

		}
		else {
			glLineWidth(5);
		}
		glBegin(GL_LINES);
		glVertex3f(-99.9f, 60, -110 + i * 6.25);
		glVertex3f(-99.9f, 25, -110 + i * 6.25);
		glEnd();

	}

	for (int i = 0; i <= 3; i++)
	{
		if (i == 0 || i == 3)
			glLineWidth(11);
		else glLineWidth(5);

		glBegin(GL_LINES);
		glVertex3f(-99.9f, 25 + i * 11.66, -110);
		glVertex3f(-99.9f, 25 + i * 11.66, -85);
		glEnd();
	}

	glPopMatrix();


	glLineWidth(1);

}

void DrawFan()
{
	glPushMatrix();

	glTranslatef(0, 75, -110);
	glRotatef(FanAngle, 0, 1, 0);

	//风扇支架
	glPushMatrix();
	glColor3ub(255, 228, 225);
	glTranslatef(0, 10, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 2, 2, 15, 30, 30);
	glPopMatrix();

	//风扇圆
	glPushMatrix();

	glPushMatrix();//draw light
	glRotatef(-90, 1, 0, 0);
	for (int i = 0; i <= 2; i++)
	{
		glTranslatef(0, 0, -i * 3);

		if (i == 2)
		{
			glColor3ub(192, 192, 192);
			gluCylinder(obj, 15 - i * 1.5, 15 - i * 1.5, 4, 30, 30);
			glPushMatrix();
			glColor3ub(247, 238, 80);
			/*glTranslatef(0, 0, -2);*/
			gluDisk(obj, 0, 15 - i * 1.5, 30, 30);
			glPopMatrix();
		}
		else {
			glColor3ub(192, 192, 192);
			gluCylinder(obj, 15 - i * 2, 15 - i * 2, 4, 30, 30);
			glPushMatrix();
			glColor3ub(247, 238, 80);
			/*glTranslatef(0, 0, -2);*/
			gluDisk(obj, 0, 15 - i * 2, 30, 30);
			glPopMatrix();

		}

	}


	glPopMatrix();

	glTranslatef(0, 7, 0);

	glRotatef(-90, 1, 0, 0);
	glColor3ub(139, 139, 131);
	gluCylinder(obj, 6, 6, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(240, 255, 240);
	gluDisk(obj, 0, 6, 30, 30);

	glTranslatef(0, 0, 3);
	glColor3ub(205, 205, 193);
	gluDisk(obj, 0, 6, 30, 30);
	glPopMatrix();

	//扇叶
	glPushMatrix();
	glColor3ub(240, 255, 255);
	glTranslatef(0, 8, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(40, 0, -5);
	glVertex3f(40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-40, 0, -5);
	glVertex3f(-40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, -40);
	glVertex3f(5, 0, -40);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, 40);
	glVertex3f(5, 0, 40);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void display(void) // Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*--------------------------------------*/

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	DrawTime();

	DrawDoor();

	DrawWalls();


	DrawWindow();

	Drawtable();

	DrawSofa();


	DrawTeapot();

	DrawFan();

	DrawDesk();

	OnDisplay();
	OnDisplay1();
	onDisplay2();
	/*----------------------------------------*/
	glutSwapBuffers();
	glFlush();

}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	//以防除数为0
	if (h == 0) h = 1;

	WinWidth = w;
	WinHeight = h;

	//将视口大小变成窗口大小
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//单位化投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 800.);
	//	上面这个不好用，注掉

	GLfloat faspect;
	faspect = (GLfloat)w / (GLfloat)h;

	gluPerspective(100.0, faspect, 0.1, 1000.0);
	gluLookAt(Eye.x, Eye.y, Eye.z,
		lookx, looky, lookz,
		0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case '\033'://press 'esc' to quit
		exit(0);
		break;

	case '1':	//open/close the door

		if (Door1 == door1_off)
			Door1 = door1_on;
		else Door1 = door1_off;
		break;

	case '5':	//open/close the tv
		if (Tv_Color_Choice == 1)
			Tv_Color_Choice = 0;
		else Tv_Color_Choice = 1;
		break;

	case '4':	//风扇旋转/停下
		if (Fan == fan_turnoff)
			Fan = fan_turnon;
		else Fan = fan_turnoff;
		break;

	case '2':	//茶壶移动/停止
		if (Teapot1 == teapot_on)
			Teapot1 = teapot_off;
		else Teapot1 = teapot_on;
		break;

	case '6':	//开/关灯
		if (Light == light_on)
		{
			Light = light_off;
			glDisable(GL_LIGHT0);
		}
		else
		{
			Light = light_on;
			glEnable(GL_LIGHT0);
		}
		break;

	case '3':	//凳子移动
		if (Chair == chair_on)
		{
			Chair = chair_off;

		}
		else
		{
			Chair = chair_on;
		}
		break;

	case '7':     // basketball back
	{
		basket_x = 0;
		basket_y = 0;
	}

	break;

	case '8':

	{
		light1_ambient[1] += 0.1;
		light1_diffuse[1] += 0.1;

		light1_ambient[2] += 0.1;
		light1_diffuse[2] += 0.1;
	}
	break;

	case 'z':
		if (Draw1 == draw1_off)
		{

			Draw1 = draw1_on;
		}
		else Draw1 = draw1_off;
		break;

	case 'x':
		if (Draw2 == draw2_off)
		{

			Draw2 = draw2_on;
		}
		else Draw2 = draw2_off;
		break;
	case 'c':
		if (Draw3 == draw3_off)
		{

			Draw3 = draw3_on;
		}
		else Draw3 = draw3_off;
		break;



	default:break;

	}

	reshape(WinWidth, WinHeight);
	glutPostRedisplay();

}

void specialkey(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_F1:

		looky += 5;
		if (up_down_angle <= 45)
			up_down_angle += 4;

		break;

	case GLUT_KEY_F2:

		looky -= 5;
		if (up_down_angle >= -45)
			up_down_angle -= 4;
		break;

	case GLUT_KEY_F3:

		lookx -= 5;
		if (personangle <= 45)
			personangle += 5;
		break;

	case GLUT_KEY_F4:

		lookx += 5;
		if (personangle >= -45)
			personangle -= 5;
		break;
	case GLUT_KEY_LEFT:
		Eye.x -= 2.0;
		lookx -= 2;
		xiaomx -= 2;

		break;

	case GLUT_KEY_RIGHT:
		Eye.x += 2.0;
		lookx += 2;
		xiaomx += 2;
		break;


	case GLUT_KEY_DOWN:
		run = run_on;
		Eye.z += 2.0;
		xiaom += 2;
		lookz += 2;
		break;

	case GLUT_KEY_UP:
		run = run_on;
		/*	legangle++;*/
		Eye.z -= 2.0;
		xiaom -= 2;
		lookz -= 2;
		break;

	default:
		break;
	}

	reshape(WinWidth, WinHeight);
	glutPostRedisplay();

}


void idle()
{
	if (Teapot1 == teapot_on)
	{
		if (teapotpositiony <= 40)
		{
			teapotpositiony++;
			Sleep(5);
		}
		if (teapotpositiony >= 40 && teapotpositionx <= 17)
		{
			teapotpositionx++;
			Sleep(5);
		}
		if (teapotpositiony >= 40 && teapotpositionx >= 17 && teapotrotatef >= -90)
		{
			teapotrotatef--;
			Sleep(5);
		}
	}
	else {
		if (teapotpositiony >= 40 && teapotpositionx >= 17 && teapotrotatef <= 1)
		{
			teapotrotatef++;
			Sleep(5);
		}
		if (teapotpositiony >= 40 && teapotpositionx >= 0 && teapotrotatef >= 0)
		{
			teapotpositionx--;
			Sleep(5);
		}
		if (teapotpositiony > 0 && teapotpositionx <= 0)
		{
			teapotpositiony--;
			Sleep(5);
		}

	}


	if (Chair == chair_off)
	{
		if (chairposition >= 0)
		{
			chairposition--;
		}
	}
	else {
		if (chairposition <= 40)
			chairposition++;
	}


	if (Draw1 == draw1_off)
	{
		if (drawerposition1 <= 7)
		{
			drawerposition1++;
		}

	}
	else {
		if (drawerposition1 >= -10)
		{
			drawerposition1--;
		}

	}

	if (Draw2 == draw2_off)
	{
		if (drawerposition2 <= 7)
		{
			drawerposition2++;
		}

	}
	else {
		if (drawerposition2 >= -10)
		{
			drawerposition2--;
		}
	}

	if (Draw3 == draw3_off)
	{
		if (drawerposition3 <= 7)
		{
			drawerposition3++;
		}

	}
	else {
		if (drawerposition3 >= -10)
		{
			drawerposition3--;
		}

	}
	if (Door1 == door1_on)
	{
		if (doorangle_1 <= 170)
			doorangle_1++;

	}
	else {
		if (doorangle_1 >= 0)
			doorangle_1--;

	}



	if (legangle >= 15 || legangle <= -15)    //control basketball on/off
	{
		Basket = basket_on;
	}
	else {
		Basket = basket_off;
	}

	if (Basket == basket_on)                  //control basketball   how to run
	{
		if (basket_x <= 50 && Basketback == basketback_off)
		{
			basket_x += 5;
			Sleep(2);
			if (basket_x == 50)
				Basketback = basketback_on;

		}
		else if (basket_x >= 0 && Basketback == basketback_on) {
			basket_x -= 5;
			Sleep(2);
			if (basket_x == 0)
				Basketback = basketback_off;
		}

		if (basket_y <= 25 && Basketfloor == basketfloor_off)
		{
			basket_y += 5;
			Sleep(2);
			if (basket_y == 25)
				Basketfloor = basketfloor_on;

		}
		else if (basket_y >= 0 && Basketfloor == basketfloor_on) {
			basket_y -= 5;
			Sleep(2);
			if (basket_y == 0)
				Basketfloor = basketfloor_off;
		}
	}
	if (run == run_on)
	{
		if (run_go)
		{
			if (legangle <= 20)
			{
				legangle += 2;
			}
			else run_go = 0;
		}
		else {

			if (legangle >= -20)
				legangle -= 2;
			else run_go = 1;
		}



		run = run_off;


	}

	if (Post == post_up)
	{

		PostPos = PostPos + 0.05;
		if (PostPos >= 80)
		{
			PostPos = 80;
			Post = postempty;
		}
	}

	if (Post == post_down)
	{
		PostPos = PostPos - 0.05;
		if (PostPos <= -100)
		{
			PostPos = -100;
			Post = postempty;
		}
	}

	if (Fan == fan_turnon)
	{
		if (FanAngle <= -360)
		{
			FanAngle = 0;
		}
		FanAngle--;
	}



	if (Teapot == teapot_translate)
	{
		if (Teapot_dire == true)
		{
			TeapotPos -= 0.1;
			if (TeapotPos < -110)
			{
				Teapot_dire = false;
			}
		}
		else
		{
			TeapotPos += 0.1;
			if (TeapotPos > -96)
			{
				Teapot_dire = true;
			}
		}
	}

	if (Stool == stoolmove)
	{
		if (Stool_dir)
		{
			StoolPos -= 1;
			if (StoolPos <= -40)
			{
				Stool = stoolstop;
				Stool_dir = false;
			}
		}
		else
		{
			StoolPos += 1;
			if (StoolPos >= 50)
			{
				Stool = stoolstop;
				Stool_dir = true;
			}

		}
	}

	if (Sphere == sphere_rotate)
	{
		if (Sphereangle >= 360)
			Sphereangle = 0;
		Sphereangle += 1;
	}


	reshape(WinWidth, WinHeight);

	glutPostRedisplay();
}


void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	//双缓冲+RGBA+深度模式
	glutInitDisplayMode(GLUT_RGBA |
		GLUT_DOUBLE | GLUT_DEPTH |
		GLUT_MULTISAMPLE);

	/*Create a window with title specified */
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("2020-1024=？");

	init();	/*not GLUT call, initialize several parameters */
	SetupRC();
	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	Initialization();
	Initialization1();
	Initialization2();
	Initialization3();
	//改变窗口大小时防止变形
	glutReshapeFunc(reshape);
	//显示
	glutDisplayFunc(display);

	glutTimerFunc(1000, timerFunc, 1);
	//键盘按键
	glutKeyboardFunc(keyboard);
	//特殊按键
	glutSpecialFunc(specialkey);
	//空闲时渲染
	glutIdleFunc(idle);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

}