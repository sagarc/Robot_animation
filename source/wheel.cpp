#include "wheel.h"

void wheel::drawCircle(float radius) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0 ,0);
	float ang=0;
	for(ang=0;ang<360;ang+=1)
	glVertex3f(sin(ang)*radius, cos(ang)*radius,0);
	glEnd();
}

void wheel::drawWheel() { 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);		
	glBindTexture(GL_TEXTURE_2D, wheeltex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wheelimagew, wheelimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, wheelimage);
	GLUquadricObj *quad = gluNewQuadric();
	gluQuadricTexture(quad,GLU_TRUE);
	glEnable(GL_TEXTURE_2D);			
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);								
	glBindTexture(GL_TEXTURE_2D, wheeltex);				
	glPushMatrix();
		glTranslatef(0.0,0.0f,wheelwidth); //outer circle of cylinder
		gluDisk(quad,0,wheelrad*1.05,20,2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);			
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);								
	glBindTexture(GL_TEXTURE_2D, wheeltex);					
	gluDisk(quad,0,wheelrad*1.05,20,2); //inner circle of cylinder
	glDisable(GL_TEXTURE_2D);
		
	glColor3f(0.3f, 0.0f, 0.0f);
	GLUquadricObj *quadObj = gluNewQuadric();	
	gluCylinder(quadObj,wheelrad, wheelrad, wheelwidth, 35,35);
	
	glColor3f(0.3f, 0.0f, 0.0f);
	GLUquadricObj *quadObj1 = gluNewQuadric();
	glPushMatrix();
		glTranslatef(0.0f,0.0f,-axlewidth);
		gluCylinder(quadObj1,axlerad, axlerad, axlewidth, 35,35);
	glPopMatrix();
	
}

GLuint wheel::createDL() {
	GLuint temp;
	temp = glGenLists(1);
	glNewList(temp,GL_COMPILE);
	drawWheel();
	glEndList();
	return(temp);
}


wheel::wheel(float bdlen) {
	initTexture();
	glGenTextures(1, texName);
	wheeltex = texName[0]; 
	bodylen = bdlen;
	wheelrad = 0.5f,wheelwidth = 0.2f,axlerad = 0.2f,axlewidth = 0.3;
	wheels = createDL();
}

wheel::~wheel() {

}

void wheel::initTexture() {
	char filename[] = "images/wheel.ppm";
	wheelimage = read_PPM(filename, &wheelimagew, &wheelimageh);
}

void wheel::draw() {
	glPushMatrix();		 	
		glTranslatef((bodylen)/2.0 + axlewidth,-0.3*bodylen,0.0f);//Translate for left wheel
	    glRotatef(90,0.0f,1.0f,0.0f); //rotating whhel by 90 degrees
		glRotatef(leftwheelang,0.0,0.0,1.0); //simple motion of wheels without movement 
		glCallList(wheels);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef( - (bodylen)/2.0 - axlewidth,-0.3*bodylen,0.0f);//Translate for left wheel
	    glRotatef(-90,0.0f,1.0f,0.0f); //rotating whhel by 90 degrees
		glRotatef(rightwheelang,0.0,0.0,1.0); //simple motion of wheels without movement 
		glCallList(wheels);
	glPopMatrix();
}

void wheel::rotate_right_wheel(int n) {	
rightwheelang -= n;	
}

void wheel::rotate_left_wheel(int n) {
leftwheelang += n;	
}

GLubyte* wheel::read_PPM(char* filename, int* width, int* height)
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
