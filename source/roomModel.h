#ifndef _roomModel_H_
#define _roomModel_H_

#include <cstdlib>
#include <GL/glut.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>

class roomModel {
private:
	GLuint texName[7];
	float cubesize;
	int cameraPos;
	float x,y,z;
	float xc, yc, zc;
	float xt, yt, zt;
	GLuint wall_list, leg_list, chair_surface_list;
	
	int tableimagew,tableimageh;
	GLubyte* tableimage;
	GLuint tabletex;
	int legimagew,legimageh;
	GLubyte* legimage;
	GLuint legtex;
	int chairimagew,chairimageh;
	GLubyte* chairimage;
	GLuint chairtex;
	int wallimagew,wallimageh;
	GLubyte* wallimage;
	GLuint walltex;
	int ceilingimagew,ceilingimageh;
	GLubyte* ceilingimage;
	GLuint ceilingtex;
	int floorimagew,floorimageh;
	GLubyte* floorimage;
	GLuint floortex;
	
	void draw_texture(GLuint texname, float bodylen);
	void draw_wall();
	void draw_chair_surface();
	void draw_leg();
	GLuint createDL_wall_list();
	GLuint createDL_leg_list();
	GLuint createDL_chair_surface_list();
	void drawWalls();
	void drawChair();
	void drawTable();
	GLubyte* read_PPM(char* filename, int* width, int* height);
	
public:
	roomModel();
	~roomModel();
	void initTexture();
	void draw();
	void setCamera(int pos);
	
};

#endif
