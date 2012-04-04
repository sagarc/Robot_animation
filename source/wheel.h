#ifndef _WHEEL_H_
#define _WHEEL_H_

#include <cstdlib>
#include <GL/glut.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

#include<cmath>

class wheel {
private:
	float wheelrad ,wheelwidth ,axlerad,axlewidth, leftwheelang, rightwheelang;
	float bodylen;
	GLuint wheels;
	GLuint texName[1];
	
	GLubyte* wheelimage;
	GLuint wheeltex;
	int wheelimagew, wheelimageh;
	
	void drawCircle(float radius);
	void drawWheel();
	GLuint createDL();
	GLubyte* read_PPM(char* filename, int* width, int* height);
	void initTexture();

public:
	wheel(float bdlen);	
	~wheel();
	
	void draw();
	void rotate_right_wheel(int i);
	void rotate_left_wheel(int i);
	float get_wheelrad() {return wheelrad;}
};

#endif
