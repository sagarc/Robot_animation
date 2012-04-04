#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

#include "robot.h"
#include "roomModel.h"
static float ratio, angle=0.0;
static float x=-12.0f, y=8.0f, z=-12.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
static bool isCamera = true;
static bool isNormal = true;
static bool isRoom = true;
robot* smalle;
roomModel* room;


void resize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifyinghal
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);  
	// Set the clipping volume
	gluPerspective(45, ratio, 0.2, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
}



void drawSmalle() {
	if(isNormal)
		gluLookAt(x, y, z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
	if(isRoom) {
		room->draw();
		smalle->draw();
	} else {
		smalle->draw();
		room->draw();
	}
}

void initScene() {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	
	//Lightening Variable Declaration
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light0_position[] = { 0.0, -3.0, 0.0, 0.0 };
	GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light0_ambient[] = {0.9, 0.2, 0.2, 1.0};
	GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light1_position[] = { -1.0, 5.0, 1.0, 0.0 };
	GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light1_ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	
	glShadeModel (GL_SMOOTH);
	
	//Material Property
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	
	//Lighting Property
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	
	glEnable(GL_DEPTH_TEST);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawSmalle();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if(key == 27) {
		exit(0);
	}
	if(key == '`') {
		if(isCamera)
			isCamera = false;
		else
			isCamera = true;
	} else if(isCamera) {
		if(key == '1') {	//Camera Will Look At Chair
			room->setCamera(1);
			smalle->setCamera(0);
			isNormal = false; isRoom = true;
		} else if(key == '2') {	//Camera will look at Table
			room->setCamera(2);
			smalle->setCamera(0);
			isNormal = false; isRoom = true;
		} else if(key == '3') {	//Camera will look at SmallE and will Follow it
			room->setCamera(0);
			smalle->setCamera(1);
			isNormal = false; isRoom = false;
		} else if(key == '4') {	//Camera Will be changed to the Eye of Smalle
			room->setCamera(0);
			smalle->setCamera(2);
			isNormal = false; isRoom = false;
		} else if(key == '5') {	//Revert Back to Normal
			room->setCamera(0);
			smalle->setCamera(0);
			isNormal = true; isRoom = true;
		}
	} else {
		smalle->keyboard(key,x,y);
	}
	glutPostRedisplay();
}


void inputKey(int key, int x, int y) {
	smalle->inputKey(key,x,y);
	glutPostRedisplay();
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("Small-E");
	
	smalle = new robot();	//Initializing the robot object
	room = new roomModel();
	initScene();

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(inputKey);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(resize);

	glutMainLoop();

	return(0);
}
