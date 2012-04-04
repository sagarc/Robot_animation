#ifndef _HAND_H_
#define _HAND_H_
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <GL/glut.h>

class hand {
private:
	float f[2][3][2];	// 0->left finger, 1->right finger .. . 0->backfinger, 1->forefinger . . . left hand . . . //lowerfinger(0), upperfinger(1)
	//float lf[3][2];	//0->backfinger, 1->forefinger . . . left hand . . . lowerfinger(0), upperfinger(1)
	//float rf[3][2];	//0->backfinger, 1->forefinger . . . right hand
	float handlen, handrad, handsoc, backfinger, forefinger;
	float fingerwr, fingerlr, fingerhr;
	float soc[2][3];	//0->left wrist, 1->right wrist(x,y,z)
	float shoulder_ang[2]; 	//angle of rotation of shoulders
	float bodylen;
	GLuint fore_fingers, back_fingers, wrists, shoulders;
	GLuint texName[1];	
	
	void draw_fore_finger();
	void draw_back_finger();
	void draw_wrist();
	void draw_shoulder();
	void draw_fingers(int t);
	void draw_hand(int t);
	
	GLuint Gluint_fore_fingers();
	GLuint Gluint_back_fingers();
	GLuint Gluint_wrist();
	GLuint Gluint_shoulder();
	GLubyte* read_PPM(char* filename, int* width, int* height);
	
	void initTexture();
public:
	int shoulderimagew,shoulderimageh;
	GLubyte* shoulderimage;
	GLuint shouldertex;
	hand(float bdlen);
	~hand();
	void draw();
	void rotate_finger(int lr, int fno, int lu, int i);
	void rotate_wrist(int lr, int a, int i);
	void rotate_shoulder(int lr ,int i);
};

#endif
