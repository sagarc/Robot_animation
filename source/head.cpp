#include "head.h"
#include <math.h>

void head::draw_neck_section() {
	GLUquadricObj *quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj, GLU_TRUE);
	glEnable(GL_TEXTURE_2D);			
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);								
	glBindTexture(GL_TEXTURE_2D, necktex);					
	gluCylinder(quadObj, radius, radius, len, 25,25);
	glDisable(GL_TEXTURE_2D);
}

void head::draw_eye() {
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
		glEdgeFlag(GL_FALSE);
		glVertex3f(0.0f, 0.2f, 0.0f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glVertex3f(-0.6f, 0.4f, 0.0f);
		glVertex3f(-0.75f, 0.15f, 0.0f);
		glVertex3f(-0.6f, 0.0f, 0.0f);
		glVertex3f(-0.4f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(0.0f, 0.2f, -0.1f);
		glVertex3f(0.0f, 0.4f, -0.1f);
		glVertex3f(-0.6f, 0.4f, -0.1f);
		glVertex3f(-0.75f, 0.15f, -0.1f);
		glVertex3f(-0.6f, 0.0f, -0.1f);
		glVertex3f(-0.4f, 0.0f, -0.1f);
	glEnd();
	glBegin(GL_QUAD_STRIP);
		glVertex3f(0.0f, 0.2f, 0.0f);
		glVertex3f(0.0f, 0.2f, -0.1f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glVertex3f(0.0f, 0.4f, -0.1f);
		glVertex3f(-0.6f, 0.4f, 0.0f);
		glVertex3f(-0.6f, 0.4f, -0.1f);
		glVertex3f(-0.75f, 0.15f, 0.0f);
		glVertex3f(-0.75f, 0.15f, -0.1f);
		glVertex3f(-0.6f, 0.0f, 0.0f);
		glVertex3f(-0.6f, 0.0f, -0.1f);
		glVertex3f(-0.4f, 0.0f, 0.0f);
		glVertex3f(-0.4f, 0.0f, -0.1f);
		glVertex3f(0.0f, 0.2f, 0.0f);
		glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();
	//Drawing EyeBall
	glScalef(1.0f, 1.0f, 0.3f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(-0.35f, 0.22f, 0.0f);
	glutSolidSphere(0.15f,10,10);  
}

GLuint head::createDL_neck() {
	GLuint necks;
	necks = glGenLists(1);
	glNewList(necks,GL_COMPILE);
	draw_neck_section();
	glEndList();
	return(necks);
}

GLuint head::createDL_eye() {
	GLuint eyes;
	eyes = glGenLists(1);
	glNewList(eyes,GL_COMPILE);
	draw_eye();
	glEndList();
	return(eyes);
}

head::head(float bdlen) {
	char neckppm[] = "images/neck.ppm";
	neckimage = read_PPM(neckppm, &(neckimagew),&(neckimageh));
	glBindTexture(GL_TEXTURE_2D, necktex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, neckimagew, neckimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, neckimage);
	
	char eyeppm[] = "images/eye.ppm";
	eyeimage = read_PPM(eyeppm, &(eyeimagew),&(eyeimageh));
	glBindTexture(GL_TEXTURE_2D, eyetex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, eyeimagew, eyeimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, eyeimage);
	
	
	//Initializing the Variables here
	necksg[0][0] = necksg[0][1] = 0.0f;
	necksg[1][0] = necksg[1][1] = 0.0f;
	necksg[2][0] = necksg[2][1] = 0.0f;
	eye[0] = eye[1] = 0.0f;
	radius = 0.1f;	len = 0.45f;
	neck_sections_list = createDL_neck();
	eye_list = createDL_eye();
	bodylen = bdlen;
	
	// direction cosines initialized
	low_neck_x=0;low_neck_y=1;low_neck_z=0;
	mid_neck_x=0;mid_neck_y=1;mid_neck_z=0;
	top_neck_x=0;top_neck_y=1;top_neck_z=0;
	front_neck_x=0;front_neck_y=0;front_neck_z=2.0f;
}

head::~head() {
	
}

void rotate_x(float ang,float& x,float& y,float& z){
	glRotatef(ang, 1.0f, 0.0f, 0.0f);
	float y1,z1;
	y1  =  cos(ang*3.1416/180)*y - sin(ang*3.1416/180)*z;
	z1  =  sin(ang*3.1416/180)*y + cos(ang*3.1416/180)*z;
	y = y1; z =z1;
}
void rotate_y(float ang,float& x,float& y,float& z){
	glRotatef(ang, 1.0f, 0.0f, 0.0f);
	float z1,x1;
	z1  =  cos(ang*3.1416/180)*z - sin(ang*3.1416/180)*x;
	x1  =  sin(ang*3.1416/180)*z + cos(ang*3.1416/180)*x;
	z = z1; x =x1;
}
void rotate_z(float ang,float& x,float& y,float& z){
	glRotatef(ang, 1.0f, 0.0f, 0.0f);
	float x1,y1;
	x1  =  cos(ang*3.1416/180)*x - sin(ang*3.1416/180)*y;
	y1  =  sin(ang*3.1416/180)*x + cos(ang*3.1416/180)*y;
	x = x1; y =y1;
}


void head::draw() {
	//drawNeckSegment();
	glPushMatrix();
		//Drawing Base Neck Segment
		glColor3f(1.0f,1.0f,1.0f);
		glTranslatef(0.0f, (bodylen/2.0), 0.0f);
		glRotatef(necksg[0][0], 1.0f, 0.0f, 0.0f);		
		glRotatef(necksg[0][1], 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(neck_sections_list);
		glPopMatrix();

		//Drawing middle Neck Segment
		glTranslatef(0.0f, len, 0.0f);
		glRotatef(necksg[1][0], 1.0f, 0.0f, 0.0f);
		glRotatef(necksg[1][1], 0.0f, 1.0f, 0.0f);
		glColor3f(0.5f,0.5f,0.5f);
		glPushMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(neck_sections_list);
		glPopMatrix();
		
		//Drawing the nose section; neck upper section
		glTranslatef(0.0f, len + 0.05f, 0.0f);
		glRotatef(necksg[2][0], 1.0f, 0.0f, 0.0f);
		glRotatef(necksg[2][1], 0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			GLUquadricObj *quadObj = gluNewQuadric();
			gluCylinder(quadObj, 0.1f, 0.04f, 0.2f, 25,25);
		glPopMatrix();
		
		//Drawing Left Eye
		glPushMatrix();
			glTranslatef(-0.05f, 0.0f, 0.0f);
			glRotatef(eye[0], 0.0f, 1.0f, 0.0f);
			glCallList(eye_list);
		glPopMatrix();
		
		//Drawing Right Eye
		glPushMatrix();
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-0.05f, 0.0f, 0.0f);
			glRotatef(eye[1], 0.0f, 1.0f, 0.0f);
			glCallList(eye_list);
		glPopMatrix();
	glPopMatrix();	
}


void head::rotate_left_eye(int n) {
	if(n==1 && eye[0]<80.0f)
		eye[0] = eye[0] + 1.0f;
	else if(eye[0]>-80.0f)
		eye[0] = eye[0] - 1.0f;
}

void head::rotate_right_eye(int n) {
	if(n==1 && eye[1]<90.0f)
		eye[1] += 1.5f;
	else if(eye[1]>-90.0f)
		eye[1] -= 1.5f;
}

void head::rotate_neck_upper_section_x(int n) {
	if(n==1 && necksg[2][0]<80.0f){
		necksg[2][0] += 1.5f;
		rotate_x(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else if(necksg[2][0]>-80.5f){
		necksg[2][0] -= 1.0f;
		rotate_x(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(-1.5,front_neck_x,front_neck_y,front_neck_z);}
}

void head::rotate_neck_upper_section_y(int n) {
	if(n==1){
		necksg[2][1] += 1.5f;
		rotate_y(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_y(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else{
		necksg[2][1] -= 1.5f;
		rotate_y(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_y(-1.5,front_neck_x,front_neck_y,front_neck_z);}
}

void head::rotate_neck_middle_section_x(int n) {
	if(n==1 && necksg[1][0]<70.0f){
		necksg[1][0] += 1.5f;
		rotate_x(1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_x(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else if(necksg[1][0]>-70.0f){
		necksg[1][0] -= 1.5f;
		rotate_x(-1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_x(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(-1.5,front_neck_x,front_neck_y,front_neck_z);}
}

void head::rotate_neck_middle_section_y(int n) {
	if(n==1){
		necksg[1][1] += 1.5f;
		rotate_y(1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_y(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_y(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else{
		necksg[1][1] -= 1.5f;
		rotate_y(-1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_y(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_y(-1.5,front_neck_x,front_neck_y,front_neck_z);}
}

void head::rotate_neck_lower_section_x(int n) {
	if(n==1 && necksg[0][0]<70.0f){
		necksg[0][0] += 1.5f;
		rotate_x(1.5,low_neck_x,low_neck_y,low_neck_z);
		rotate_x(1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_x(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else if(necksg[0][0]>-70.0f){
		necksg[0][0] -= 1.5f;
		rotate_x(-1.5,low_neck_x,low_neck_y,low_neck_z);
		rotate_x(-1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_x(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_x(-1.5,front_neck_x,front_neck_y,front_neck_z);}
}

void head::rotate_neck_lower_section_z(int n) {
	if(n==1 && necksg[0][1]<70.0f){
		necksg[0][1] += 1.5f;
		rotate_z(1.5,low_neck_x,low_neck_y,low_neck_z);
		rotate_z(1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_z(1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_z(1.5,front_neck_x,front_neck_y,front_neck_z);}
	else if(necksg[0][1]>-70.0f){
		necksg[0][1] -= 1.5f;
		rotate_z(-1.5,low_neck_x,low_neck_y,low_neck_z);
		rotate_z(-1.5,mid_neck_x,mid_neck_y,mid_neck_z);
		rotate_z(-1.5,top_neck_x,top_neck_y,top_neck_z);
		rotate_z(-1.5,front_neck_x,front_neck_y,front_neck_z);
		}
}
void head::reset_config() {
	necksg[0][0] = necksg[0][1] = 0.0f;
	necksg[1][0] = necksg[1][1] = 0.0f;
	necksg[2][0] = necksg[2][1] = 0.0f;
	eye[0] = eye[1] = 0.0f;
	radius = 0.1f;	len = 0.55f;
}


GLubyte* head::read_PPM(char* filename, int* width, int* height)
{
	FILE* fp;
	int i, w, h, d;
	GLubyte* image;
	char head[70];          /* max line <= 70 in PPM (per spec). */
	fp = fopen(filename, "rb");
	if (!fp) {
		perror(filename);
		return NULL;
	}
	/* grab first two chars of the file and make sure that it has the
	   correct magic cookie for a raw PPM file. */
	fgets(head, 70, fp);
	if (strncmp(head, "P6", 2)) {
		fprintf(stderr, "%s: Not a raw PPM file\n", filename);
		return NULL;
	}
	/* grab the three elements in the header (width, height, maxval). */
	i = 0;
	while(i < 3) {
		fgets(head, 70, fp);
		if (head[0] == '#')     /* skip comments. */
			continue;
		if (i == 0)
			i += sscanf(head, "%d %d %d", &w, &h, &d);
		else if (i == 1)
			i += sscanf(head, "%d %d", &h, &d);
		else if (i == 2)
			i += sscanf(head, "%d", &d);
	}
	/* grab all the image data in one fell swoop. */
	image = (GLubyte*)malloc(sizeof(GLubyte)*w*h*3);
	fread(image, sizeof(GLubyte), w*h*3, fp);
	fclose(fp);
	*width = w;
	*height = h;
	return image;
}
