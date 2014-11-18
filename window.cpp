#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include <time.h>
#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"
#include "Robot.h"
#include "MatrixTransform.h"
#include "Cube4.h"

#define PI 3.14159265

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

int toggle = 0;
int mode = 1;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	//if (toggle == 1)
		//Globals::cube.spin(-0.5);   // rotate cube; if it spins too fast try smaller values and vice versa
	//else
		//Globals::cube.spin(0.5);
  displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);  // set new viewport size
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);

  Globals::camera.setFrustum(60.0, double(width) / (double)height, 1.0, 1000.0);
}

//What I'm Adding

/* Not needed for Lab 4
float bunnyCoor[36000][6];
float dragonCoor[110000][6];

float bunnyScale = 0;
float bunnyMidX = 0;
float bunnyMidY = 0;
float bunnyMidZ = 0;

float dragonScale = 0;
float dragonMidX = 0;
float dragonMidY = 0;
float dragonMidZ = 0;

void Window::loadBunny()
{
	float vert1, vert2, vert3, norm1, norm2, norm3;
	FILE* bunny;
	bunny = fopen("bunny.xyz", "r");

	float maxX = 0;
	float maxY = -1;
	float maxZ = 0;

	float minX = 0;
	float minY = 1;
	float minZ = 0;

	for (int i = 0; i < 36000; i++)
	{
		if (fscanf(bunny, "%f %f %f %f %f %f", &vert1, &vert2, &vert3, &norm1, &norm2, &norm3) == 6)
		{
			bunnyCoor[i][0] = vert1;

			maxX = fmaxf(maxX, bunnyCoor[i][0]);
			minX = fminf(minX, bunnyCoor[i][0]);

			bunnyCoor[i][1] = vert2;
			maxY = fmaxf(maxY, bunnyCoor[i][1]);
			minY = fminf(minY, bunnyCoor[i][1]);

			bunnyCoor[i][2] = vert3;
			maxZ = fmaxf(maxZ, bunnyCoor[i][2]);
			minZ = fminf(minZ, bunnyCoor[i][2]);

			bunnyCoor[i][3] = norm1;
			bunnyCoor[i][4] = norm2;
			bunnyCoor[i][5] = norm3;
		}
	}

	float len = 40 * tan(30 * PI / 180);
	bunnyScale = (len / (maxY - minY));

	bunnyMidX = minX + (maxX - minX) / 2;
	bunnyMidY = minY + (maxY - minY) / 2;
	bunnyMidZ = minZ + (maxZ - minZ) / 2;

	fclose(bunny);
}

void Window::loadDragon()
{
	float vert1, vert2, vert3, norm1, norm2, norm3;
	FILE* dragon;
	dragon = fopen("dragon.xyz", "r");

	float maxX = 0;
	float maxY = -1;
	float maxZ = 0;

	float minX = 0;
	float minY = 1;
	float minZ = 0;

	for (int i = 0; i < 110000; i++)
	{
		if (fscanf(dragon, "%f %f %f %f %f %f", &vert1, &vert2, &vert3, &norm1, &norm2, &norm3) == 6)
		{
			dragonCoor[i][0] = vert1;

			maxX = fmaxf(maxX, dragonCoor[i][0]);
			minX = fminf(minX, dragonCoor[i][0]);

			dragonCoor[i][1] = vert2;
			maxY = fmaxf(maxY, dragonCoor[i][1]);
			minY = fminf(minY, dragonCoor[i][1]);

			dragonCoor[i][2] = vert3;
			maxZ = fmaxf(maxZ, dragonCoor[i][2]);
			minZ = fminf(minZ, dragonCoor[i][2]);

			dragonCoor[i][3] = norm1;
			dragonCoor[i][4] = norm2;
			dragonCoor[i][5] = norm3;
		}
	}

	float len = 40 * tan(30 * PI / 180);
	dragonScale = (len / (maxY - minY));

	dragonMidX = minX + (maxX - minX) / 2;
	dragonMidY = minY + (maxY - minY) / 2;
	dragonMidZ = minZ + (maxZ - minZ) / 2;

	fclose(dragon);
}

//End of What I Added

// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall

	*/

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.

Window window;

Matrix4& Window::getModelViewMatrix()
{
	return modelView;
}

Matrix4& Window::getCameraMatrix()
{
	return camera;
}

Matrix4 Window::setScaleMatrix(float factor)
{
	Matrix4 scale;
	scale.makeScale(factor, factor, factor);
	return scale;
}

void Window::updateModelViewMatrix()
{
	modelView = camera*model;
}

Window::Window()
{
	model.identity();
	camera = Globals::camera.getInverseCamera();
	updateModelViewMatrix();
}

float rotateAngle = 0;
int fuckyou = 0;
int boundingSphere = 0;
int numRobots = 20;
clock_t Start = clock();
int noculltimer = 0;
int frame = 0;

extern int frustum = 0;
extern int renderInt = 0;
extern int bound = 0;
extern int box = 0;

void Window::displayCallback()
{

	//What I'm adding for lab 3
	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  glLoadMatrixd(Globals::camera.c.getPointer());

  Globals::camera.setPlane();

  //Lab 4 

  if (frustum == 1)
  {
	  for (int i = 0; i < numRobots; i++)
	  {
		  for (int j = 0; j < numRobots; j++)
		  {
			  renderInt = 0;

			  Matrix4 translate;
			  translate.makeTranslate(i * 20, 0, j * 20);
			  MatrixTransform transMatrix(translate);

			  MatrixTransform bound;
			  bound.addChild(&wireSphere());
			  transMatrix.addChild(&bound);

			  transMatrix.draw(Globals::camera.c);

			  if (renderInt == 1)
			  {
				  Robot myBot(rotateAngle, i * 20, j * 20, boundingSphere, frustum);
				  myBot.draw(Globals::camera.c);

				  if (fuckyou)
					  rotateAngle += .05;
				  else
					  rotateAngle += -.05;
				  if (rotateAngle > 75)
					  fuckyou = 0;
				  if (rotateAngle < -75)
					  fuckyou = 1;
			  }
		  }
	  }
  }

  else
  {
	  for (int i = 0; i < numRobots; i++)
	  {
		  for (int j = 0; j < numRobots; j++)
		  {
			Matrix4 translate;
			translate.makeTranslate(i * 20, 0, j * 20);
			MatrixTransform transMatrix(translate);

			MatrixTransform bound;
			bound.addChild(&wireSphere());
			transMatrix.addChild(&bound);

			transMatrix.draw(Globals::camera.c);

			Robot myBot(rotateAngle, i * 20, j * 20, boundingSphere, frustum);
			myBot.draw(Globals::camera.c);

			if (fuckyou)
				rotateAngle += .05;
			else
				rotateAngle += -.05;
			if (rotateAngle > 75)
				fuckyou = 0;
			if (rotateAngle < -75)
				fuckyou = 1;
		  }
	  }
  }


  float time = glutGet(GLUT_ELAPSED_TIME);
  frame++;
  if (time - noculltimer > 1000)
  {
	  float fps = frame*1000.0 / (time - noculltimer);
	  noculltimer = time;
	  frame = 0;
	  if (frustum == 0)
		  cout << "no culling FPS: " << fps << endl;
	  else
		  cout << "culling FPS: " << fps << endl;
  }

  //End of Lab 4

  //What i'm adding
  
  /* Not needed for Lab 4
  Matrix4 dragTranslate;
  dragTranslate.makeTranslate(-dragonMidX, -dragonMidY, -dragonMidZ);

  Matrix4 dragScale;
  dragScale.makeScale(dragonScale, dragonScale, dragonScale);

  Matrix4 bunnyTranslate;
  bunnyTranslate.makeTranslate(-bunnyMidX, -bunnyMidY, -bunnyMidZ);

  Matrix4 bunnyScaling;
  bunnyScaling.makeScale(bunnyScale, bunnyScale, bunnyScale);

  //End of what I added
  
  if (mode == 1)
  {
	  // Tell OpenGL what ModelView matrix to use:
	  Matrix4 glmatrix;
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());


	  // Draw all six faces of the cube:
	  glBegin(GL_QUADS);
	  glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	  // To change the color of the other faces you will need to repeat this call before each face is drawn.
	  // Draw front face:
	  glNormal3f(0.0, 0.0, 1.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw left side:
	  glNormal3f(-1.0, 0.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw right side:
	  glNormal3f(1.0, 0.0, 0.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);

	  // Draw back face:
	  glNormal3f(0.0, 0.0, -1.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);

	  // Draw top side:
	  glNormal3f(0.0, 1.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(-5.0, 5.0, -5.0);

	  // Draw bottom side:
	  glNormal3f(0.0, -1.0, 0.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);
	  glEnd();
  }
  
  //What I'm Adding for Lab 2

  else if (mode == 2)
  {
	  Matrix4 glmatrix;
	  glmatrix = Globals::camera.getGLMatrix1();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  glBegin(GL_TRIANGLES);

	  int index;
	  float color;
	  float vertex;
	  float vertex2;
	  float vertex3;
	  for (int i = 0; i <= 59; i++)
	  {
		  index = indices[i];

		  color = colors[index * 3];
		  float color2 = colors[(index * 3) + 1];
		  float color3 = colors[(index * 3) + 2];
		  glColor3f(color, color2, color3);

		  vertex = vertices[index * 3];
		  vertex2 = vertices[(index * 3) + 1];
		  vertex3 = vertices[(index * 3) + 2];
		  glVertex3f(vertex, vertex2, vertex3);
	  }
	  glEnd();
  }

  else if (mode == 3)
  {
	  Matrix4 glmatrix;
	  glmatrix = Globals::camera.getGLMatrix2();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  glBegin(GL_TRIANGLES);

	  int index;
	  float color;
	  float vertex;
	  float vertex2;
	  float vertex3;

	  for (int i = 0; i <= 59; i++)
	  {
		  index = indices[i];

		  color = colors[index * 3];
		  float color2 = colors[(index * 3) + 1];
		  float color3 = colors[(index * 3) + 2];
		  glColor3f(color, color2, color3);

		  vertex = vertices[index * 3];
		  vertex2 = vertices[(index * 3) + 1];
		  vertex3 = vertices[(index * 3) + 2];
		  glVertex3f(vertex, vertex2, vertex3);
	  }
	  glEnd();
  }

  if (mode == 4)
  {
	  Matrix4 glmatrix;
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  glBegin(GL_POINTS);
	  glPointSize(5.0);

	  for (int i = 0; i < 36000; i++)
	  {
		  Vector4 bunny = Vector4(bunnyCoor[i][0], bunnyCoor[i][1], bunnyCoor[i][2], 1);
		  Vector3 normBunny = Vector3(bunnyCoor[i][3], bunnyCoor[i][4], bunnyCoor[i][5]);

		  bunny = bunnyTranslate*bunny;
		  bunny = bunnyScaling*bunny;

		  glNormal3d(normBunny.x, normBunny.y, normBunny.z);
		  glVertex3d(bunny.x, bunny.y, bunny.z);
	  }

	  glEnd();
  }

  if (mode == 5)
  {

	  Matrix4 glmatrix;
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  glBegin(GL_POINTS);
	  glPointSize(5.0);

	  for (int i = 0; i < 110000; i++)
	  {
		  Vector4 dragon = Vector4(dragonCoor[i][0], dragonCoor[i][1], dragonCoor[i][2], 1);
		  Vector3 normDragon = Vector3(dragonCoor[i][3], dragonCoor[i][4], dragonCoor[i][5]);

		  dragon = dragTranslate*dragon;
		  dragon = dragScale*dragon;

		  glNormal3d(normDragon.x, normDragon.y, normDragon.z);
		  glVertex3d(dragon.x, dragon.y, dragon.z);
	  }



	  glEnd();

	  
  }
  //End of What I added for Lab 2

  */
  
  glFlush();  
  glutSwapBuffers();

   //End of what I addd for lab 3
}

//What I'm Adding

void Window::keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 66:
			box = !box;
			break;
		case 98:
			bound = !bound;
			break;
		case 99:
			frustum = !frustum;
			break;
		case 120:
			Globals::cube.moveLeftRight(-2);
			break;
		case 88:
			Globals::cube.moveLeftRight(2);
			break;
		case 121:
			Globals::cube.moveUpDown(-2);
			break;
		case 89:
			Globals::cube.moveUpDown(2);
			break;
		case 122:
			Globals::cube.moveOutIn(2);
			break;
		case 90:
			Globals::cube.moveOutIn(-2);
			break;
		case 114:
			Globals::cube.reset();
			break;
		case 111:
			Globals::cube.orbit(10);
			break;
		case 79:
			Globals::cube.orbit(-10);
			break;
		case 115:
			Globals::cube.scale(0.9, 0.9, 0.9);
			break;
		case 83:
			Globals::cube.scale(1.1, 1.1, 1.1);
			break;
		case 116:
			if (toggle == 0)
				toggle = 1;
			else
				toggle = 0;
			break;
		default:
			break;
	}
	Matrix4 displayMatrix;
	displayMatrix = Globals::cube.getMatrix();
	//displayMatrix.printInfo();
}

void Window::specialFuncCallback(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F1:
			mode = 1;
			break;
		case GLUT_KEY_F2:
			mode = 2;
			break;
		case GLUT_KEY_F3:
			mode = 3;
			break;
		case GLUT_KEY_F4:
			mode = 4;
			break;
		case GLUT_KEY_F5:
			mode = 5;
			break;
		default:
			break;
	}
}
//End of What I'm Adding
