#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <cstdlib>
#include <GL/glut.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "hand.h"
#include "head.h"
#include "wheel.h"

class robot {
private:
	float bodylen;
	float angles[3];	//Corresponding to the three axis
	float transx, transy, transz;	//Corresponding to the three directions
	float movement;
	float x,y,z;
	int cameraPos;	//For Specifying Camera Position	
	hand* robot_hand;
	head* robot_head;
	wheel* robot_wheel;
	GLuint texName[1];
	GLubyte* bodyimage;
	GLuint bodytex;
	int bodyimagew, bodyimageh;
	
	void rotate_robot(int a, int i);
	void translate_robot();
	
	float myabs(float n);
	GLubyte* read_PPM(char* filename, int* width, int* height);
	void texture_body();
	
public:
	robot();
	~robot();
	void initTexture();
	void draw();
		
	void inputKey(int key, int x, int y);
	void keyboard(unsigned char key, int x, int y);
	void setCamera(int pos);
};

#endif
