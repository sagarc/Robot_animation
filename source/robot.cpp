#include "robot.h"


void robot::rotate_robot(int a, int i) {	//i will be 1 or -1
	angles[a] += i*0.1f;
}
void robot::translate_robot() {
	//To be done by sagar
}

float robot::myabs(float n) {
	if(n<0)
		return -1.0f*n;
	else
		return n;
}

GLubyte* robot::read_PPM(char* filename, int* width, int* height)
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

void robot::texture_body(){
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/*glBindTexture(GL_TEXTURE_2D, bodytex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bodyimagew, bodyimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, bodyimage);*/
	
	glEnable(GL_TEXTURE_2D);			
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);			
	glBindTexture(GL_TEXTURE_2D, bodytex);			
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-bodylen/2, -bodylen/2, bodylen/2); //front
	glTexCoord2f(0.0, 1.0); glVertex3f(-bodylen/2, bodylen/2, bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(bodylen/2, bodylen/2, bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(bodylen/2, -bodylen/2, bodylen/2);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(bodylen/2, -bodylen/2, bodylen/2); //right
	glTexCoord2f(0.0, 1.0); glVertex3f(bodylen/2, bodylen/2,  bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(bodylen/2, bodylen/2,  -bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(bodylen/2, -bodylen/2, -bodylen/2);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(bodylen/2, -bodylen/2, -bodylen/2); //back
	glTexCoord2f(0.0, 1.0); glVertex3f(bodylen/2,  bodylen/2, -bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-bodylen/2, bodylen/2, -bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-bodylen/2,-bodylen/2, -bodylen/2);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-bodylen/2, -bodylen/2, -bodylen/2); //left
	glTexCoord2f(0.0, 1.0); glVertex3f(-bodylen/2, bodylen/2, -bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-bodylen/2, bodylen/2, bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-bodylen/2, -bodylen/2, bodylen/2);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-bodylen/2, bodylen/2, bodylen/2); //top
	glTexCoord2f(0.0, 1.0); glVertex3f(-bodylen/2, bodylen/2, -bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(bodylen/2, bodylen/2, -bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(bodylen/2, bodylen/2, bodylen/2);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-bodylen/2, -bodylen/2, -bodylen/2); //bottom
	glTexCoord2f(0.0, 1.0); glVertex3f(-bodylen/2, -bodylen/2, bodylen/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(bodylen/2, -bodylen/2, bodylen/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(bodylen/2, -bodylen/2, -bodylen/2);
	glEnd();
	
	glFlush();
	glDisable(GL_TEXTURE_2D);
}

robot::robot() {		
	transx =  0.0f;
	transy = 1.0f;
	transz = 0.0f;
	angles[0] = angles[1] = angles[2] = 0.0f;
	bodylen = 1.6f;
	cameraPos = 0;
	x=-12.0f; y=8.0f; z=-12.0f;
	robot_hand = new hand(bodylen);
	robot_head = new head(bodylen);
	robot_wheel = new wheel(bodylen);
	movement = 0;
	
	initTexture();
	glGenTextures(1, texName);
	bodytex = texName[0];
	glBindTexture(GL_TEXTURE_2D, bodytex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bodyimagew, bodyimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, bodyimage);
	
}

robot::~robot() {
	delete robot_hand;
	delete robot_head;
	delete robot_wheel;
}

void robot::initTexture() {
	char filename[] = "images/body.ppm";
	bodyimage = read_PPM(filename, &(bodyimagew),&(bodyimageh));
}

void robot::draw() {
	if(cameraPos == 1) {	//Set Lookup Vector on SmallE
		gluLookAt(x, y, z, transx, 0.3f, transz, 0.0f, 1.0f, 0.0f);
	} else if (cameraPos == 2) 
	{	//Set Lookup Vector in Eye of SmallE
		float low_neck_x = robot_head->low_neck_x;float mid_neck_x = robot_head->mid_neck_x;
		float low_neck_y = robot_head->low_neck_y;float mid_neck_y = robot_head->mid_neck_y;
		float low_neck_z = robot_head->low_neck_z;float mid_neck_z = robot_head->mid_neck_z;
		float top_neck_x = robot_head->top_neck_x;float front_neck_x = robot_head->front_neck_x;
		float top_neck_y = robot_head->top_neck_y;float front_neck_y = robot_head->front_neck_y;
		float top_neck_z = robot_head->top_neck_z;float front_neck_z = robot_head->front_neck_z;			
		float necklen = robot_head->len;
		
		float xbase = transx + necklen*low_neck_x  + necklen*mid_neck_x;
		float ybase = transy + ((bodylen/2) + necklen*low_neck_y + necklen*mid_neck_y)*1.2;
		float zbase = 0.2f + transz + necklen*low_neck_z + necklen*mid_neck_z;
		
		float refx =front_neck_x; 
		float refy =front_neck_y;
		float refz =front_neck_z;			
		float refz1 =  cos(angles[1]*3.1416/180)*refz - sin(angles[1]*3.1416/180)*refx;
		float refx1  =  sin(angles[1]*3.1416/180)*refz + cos(angles[1]*3.1416/180)*refx;
		refx=refx1 + xbase;
		refy= refy + ybase;
		refz= refz1 + zbase;			
		
		float upx = top_neck_x*0.1f;
		float upy = top_neck_y*0.1f;
		float upz = top_neck_z*0.1f;
		gluLookAt(xbase, ybase ,zbase , refx, refy, refz, upx, upy, upz);
	}
	
	transx += movement*sin(angles[1]*3.1416/180);
	transz += movement*cos(angles[1]*3.1416/180);
	movement = 0;
	
	glPushMatrix();
		glScalef(1.2f, 1.2f, 1.2f);
		//glTranslatef(0.0f, 1.0f, 0.0f);
		glTranslatef(transx,transy,transz);
		glRotatef(angles[0], 1.0f, 0.0f, 0.0f);
		glRotatef(angles[1], 0.0f, 1.0f, 0.0f);
		glRotatef(angles[2], 0.0f, 0.0f, 1.0f);
		glColor3f(0.92578125f, 0.61328125f, 0.109375f);
		texture_body();	//drawing texture mapped cube
		glPushMatrix();
			robot_head->draw();
		glPopMatrix();
		glPushMatrix();
			robot_hand->draw();
		glPopMatrix();
		glPushMatrix();
			robot_wheel->draw();
		glPopMatrix();
	glPopMatrix();
}

void robot::inputKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT : angles[1] += 2.0f; break;
		case GLUT_KEY_RIGHT : angles[1] -= 2.0f; break;
		case GLUT_KEY_UP : //transx += (0.5f * sin(angles[1]*3.14159265/180.0)); transz += (0.5f * cos(angles[1]*3.14159265/180.0)); 
							movement = 0.5f;
							robot_wheel->rotate_left_wheel(10); robot_wheel->rotate_right_wheel(10);break;
		case GLUT_KEY_DOWN : //transx -= (0.5f * sin(angles[1]*3.14159265/180.0)); transz -= (0.5f * cos(angles[1]*3.14159265/180.0));
							movement = -0.5f;
							robot_wheel->rotate_left_wheel(-10); robot_wheel->rotate_right_wheel(-10);break;
	}
}

void robot::keyboard(unsigned char key, int x, int y) 
{
	switch(key){
	case 27: exit(0);break;
	case 'z':robot_hand->rotate_shoulder(0,1);break;
	case 'Z':robot_hand->rotate_shoulder(0,-1);break;
	case 'x':robot_hand->rotate_shoulder(1,1);break;
	case 'X':robot_hand->rotate_shoulder(1,-1);break;
	
	case 'q':robot_hand->rotate_wrist(0,0,1);break;
	case 'Q':robot_hand->rotate_wrist(0,0,-1);break;
	case 'w':robot_hand->rotate_wrist(0,1,1);break;
	case 'W':robot_hand->rotate_wrist(0,1,-1);break;
	case 'e':robot_hand->rotate_wrist(0,2,1);break;
	case 'E':robot_hand->rotate_wrist(0,2,-1);break;
	case 'r':robot_hand->rotate_finger(0,0,0,1);break;
	case 'R':robot_hand->rotate_finger(0,0,0,-1);break;
	case 't':robot_hand->rotate_finger(0,1,0,1);break; 
	case 'T':robot_hand->rotate_finger(0,1,0,-1);break; 
	case 'y':robot_hand->rotate_finger(0,2,0,1);break; 
	case 'Y':robot_hand->rotate_finger(0,2,0,-1);break; 
	case 'u':robot_hand->rotate_finger(0,0,1,1);break; 
	case 'U':robot_hand->rotate_finger(0,0,1,-1);break; 
	case 'i':robot_hand->rotate_finger(0,1,1,1);break; 
	case 'I':robot_hand->rotate_finger(0,1,1,-1);break; 
	case 'o':robot_hand->rotate_finger(0,2,1,1);break; 
	case 'O':robot_hand->rotate_finger(0,2,1,-1);break; 
	case 'a':robot_hand->rotate_wrist(1,0,1);break;
	case 'A':robot_hand->rotate_wrist(1,0,-1);break;
	case 's':robot_hand->rotate_wrist(1,1,1);break;
	case 'S':robot_hand->rotate_wrist(1,1,-1);break;
	case 'd':robot_hand->rotate_wrist(1,2,1);break;
	case 'D':robot_hand->rotate_wrist(1,2,-1);break;
	case 'f':robot_hand->rotate_finger(1,0,0,1);break; 
	case 'F':robot_hand->rotate_finger(1,0,0,-1);break; 
	case 'g':robot_hand->rotate_finger(1,1,0,1);break; 
	case 'G':robot_hand->rotate_finger(1,1,0,-1);break; 
	case 'h':robot_hand->rotate_finger(1,2,0,1);break; 
	case 'H':robot_hand->rotate_finger(1,2,0,-1);break; 
	case 'j':robot_hand->rotate_finger(1,0,1,1);break; 
	case 'J':robot_hand->rotate_finger(1,0,1,-1);break; 
	case 'k':robot_hand->rotate_finger(1,1,1,1);break; 
	case 'K':robot_hand->rotate_finger(1,1,1,-1);break; 
	case 'l':robot_hand->rotate_finger(1,2,1,1);break; 
	case 'L':robot_hand->rotate_finger(1,2,1,-1);break; 
	
	case 'c': robot_wheel->rotate_left_wheel(4);break;
	case 'C': robot_wheel->rotate_left_wheel(-4);break;
	case 'v': robot_wheel->rotate_right_wheel(4);break;
	case 'V': robot_wheel->rotate_right_wheel(-4);break;
	
	//Below Keys Are Working Properly Until *
	case '!' :
		robot_head->rotate_left_eye(1);break;
	case '1' :
		robot_head->rotate_left_eye(-1);break;
	case '@' :
		robot_head->rotate_right_eye(1);break;
	case '2' :
		robot_head->rotate_right_eye(-1);break;
	case '3' :
		robot_head->rotate_neck_upper_section_x(1);break;
	case '#' :
		robot_head->rotate_neck_upper_section_x(-1);break;
	case '4' :
		robot_head->rotate_neck_upper_section_y(1);break;
	case '$' :
		robot_head->rotate_neck_upper_section_y(-1);break;
	case '5' :
		robot_head->rotate_neck_middle_section_x(1);break;
	case '%' :
		robot_head->rotate_neck_middle_section_x(-1);break;
	case '6' :
		robot_head->rotate_neck_middle_section_y(1);break;
	case '^' :
		robot_head->rotate_neck_middle_section_y(-1);break;
	case '7' :
		robot_head->rotate_neck_lower_section_x(1);break;
	case '&' :
		robot_head->rotate_neck_lower_section_x(-1);break;
	case '8' :
		robot_head->rotate_neck_lower_section_z(1);break;
	case '*' :
		robot_head->rotate_neck_lower_section_z(-1);break;
	case 'b':
		angles[0] += 2.0f;break;
	case 'B':
		angles[0] -= 2.0f;break;
	case 'n':
		angles[1] += 2.0f;break;
	case 'N':
		angles[1] -= 2.0f;break;
	case 'm':
		angles[2] += 2.0f;break;
	case 'M':
		angles[2] -= 2.0f;break;
	case '~':
		transx = 0.0f; transz = -10.0f; angles[0] = angles[1] = angles[2] = 0.0f;
		robot_head->reset_config();
		break;
	}
	
}

void robot::setCamera(int pos) {
	cameraPos = pos;
}
