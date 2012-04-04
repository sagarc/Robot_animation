#ifndef _HEAD_H_
#define _HEAD_H_

#include <cstdlib>
#include <GL/glut.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

class head {
private:
	float necksg[3][2];	//Lower Neck Segment Angles, Middle Neck Segment Angles, Segment between two eyes
	float eye[2];	//0->left eye angle, 1->right eye angle
	float radius;
	float bodylen;	
	
	void draw_neck_section();
	void draw_eye();
	GLuint neck_sections_list, eye_list;
	GLuint createDL_neck();
	GLuint createDL_eye();
	
	int neckimagew,neckimageh;
	GLubyte* neckimage;
	GLuint necktex;
	int eyeimagew,eyeimageh;
	GLubyte* eyeimage;
	GLuint eyetex;
	
public:
	// to store direction cosines of neck segments
	float len;
	float low_neck_x,low_neck_y,low_neck_z;
	float mid_neck_x,mid_neck_y,mid_neck_z;
	float top_neck_x,top_neck_y,top_neck_z;
	float front_neck_x,front_neck_y,front_neck_z;
	
	head(float bdlen);
	~head();
	
	void draw();
	void rotate_left_eye(int n);
	void rotate_right_eye(int n);
	void rotate_neck_upper_section_x(int n);
	void rotate_neck_upper_section_y(int n);
	void rotate_neck_middle_section_x(int n);
	void rotate_neck_middle_section_y(int n);
	void rotate_neck_lower_section_x(int n);
	void rotate_neck_lower_section_z(int n);
	void reset_config();
	GLubyte* read_PPM(char* filename, int* width, int* height);
};

#endif
