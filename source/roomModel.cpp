#include "roomModel.h"


void roomModel::draw_texture(GLuint texname, float bodylen){
	glEnable(GL_TEXTURE_2D);			
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);										
	glBindTexture(GL_TEXTURE_2D, texname);			
			
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
	
	glNormal3d(0,1,0);
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




void roomModel::draw_wall() {
	glPushMatrix();
		glScalef(cubesize, cubesize, 0.01f);
		draw_texture(walltex,1.0f);
	glPopMatrix();
}
void roomModel::draw_chair_surface() {
	glPushMatrix();
		glScalef(1.0f, 0.15f, 1.0f);
		draw_texture(chairtex,1.0f);
		std::cout<<glGetError();
	glPopMatrix();
}
void roomModel::draw_leg() {
	glPushMatrix();
		glScalef(0.10f, 1.0f, 0.10f);
		glColor3f(0.88671875f, 0.6953125f, 0.125f);
		draw_texture(legtex,1.0f);
	glPopMatrix();
}
GLuint roomModel::createDL_wall_list() {
	GLuint temp_walls;
	temp_walls = glGenLists(1);
	glNewList(temp_walls,GL_COMPILE);
	draw_wall();
	glEndList();
	return(temp_walls);
}
GLuint roomModel::createDL_leg_list() {
	GLuint legs;
	legs = glGenLists(1);
	glNewList(legs,GL_COMPILE);
	draw_leg();
	glEndList();
	return(legs);
}
GLuint roomModel::createDL_chair_surface_list() {
	GLuint surfaces;
	surfaces = glGenLists(1);
	glNewList(surfaces,GL_COMPILE);
	draw_chair_surface();
	glEndList();
	return(surfaces);
}
void roomModel::drawWalls() {
	glPushMatrix();
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0.0f, cubesize/2.0f, 0.0f);
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				glColor3f(0.8f, 0.8f, 0.8f);
				//glCallList(wall_list);	//Top Floor
				glScalef(cubesize, cubesize, 0.01f);
				draw_texture(ceilingtex,1.0f);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, -1.0f * cubesize / 2.0f, 0.0f);
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				glColor3f(0.3f, 0.3f, 0.3f);
				//glCallList(wall_list);	//Bottom Floor
				glScalef(cubesize, cubesize, 0.01f);
				draw_texture(floortex,1.0f);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, cubesize/2.0f);
			glColor3f(0.25f, 0.25f, 0.25f);
			glCallList(wall_list);	//Front Wall
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.0 * cubesize/2.0f);
			glColor3f(0.25f, 0.25f, 0.25f);
			glCallList(wall_list);	//Back Wall
		glPopMatrix();
		glPushMatrix();
			glPushMatrix();
				glTranslatef(-1.0f * cubesize / 2.0f, 0.0f, 0.0f);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				glColor3f(0.24609375f, 0.546875f, 0.84765625f);
				glCallList(wall_list);	//left Wall
			glPopMatrix();
			glPushMatrix();
				glTranslatef(cubesize / 2.0f, 0.0f, 0.0f);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				glColor3f(0.24609375f, 0.546875f, 0.84765625f);
				glCallList(wall_list);	//Right Wall
			glPopMatrix();
		glPopMatrix();	
	glPopMatrix();
}
void roomModel::drawChair() {
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.4f, -0.40f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glCallList(chair_surface_list);	//Back Surface
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glCallList(chair_surface_list);	//Sitting Surface
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.4f, 0.5f, 0.4f);	//leg1
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.4f, 0.5f, 0.4f);	//leg2
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.4f, 0.5f, -0.4f);	//leg3
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.4f, 0.5f, -0.4f);	//leg4
			glCallList(leg_list);
		glPopMatrix();
		
		glScalef(1.0f, 1.0f, 0.7f);
		
		glPushMatrix();
			glTranslatef(-0.5f, 1.35f, 0.0f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.5f, 1.35f, 0.0f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glCallList(leg_list);
		glPopMatrix();
	glPopMatrix();
}
void roomModel::drawTable() {
	
	glPushMatrix();
		glPushMatrix();
			glScalef(2.0f, 0.1f, 3.0f);
			glTranslatef(0.0f, 10.0f, 0.0f);
			glColor3f(0.4546f, 0.45775f, 0.67865625f);
			draw_texture(tabletex,1.0f);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.9f, 0.5f, 1.43f);
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.9f, 0.5f, 1.43f);
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.9f, 0.5f, -1.43f);
			glCallList(leg_list);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.9f, 0.5f, -1.43f);
			glCallList(leg_list);
		glPopMatrix();
	glPopMatrix();
}

GLubyte* roomModel::read_PPM(char* filename, int* width, int* height)
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


roomModel::roomModel() {
	cameraPos = 0;
	cubesize = 10.0f;
	x=-8.0f; y=8.0f; z=-12.0f;
	xc=2.5f; yc=1.0f; zc=-4.0f;
	xt=-3.0f; yt=1.5f; zt=0.0f;
	glGenTextures(6, texName);
	tabletex = texName[0];
	chairtex = texName[1];
	legtex = texName[2];
	walltex = texName[3];
	ceilingtex = texName[4];
	floortex = texName[5];
	char tableppm[] = "images/table.ppm";
	tableimage = read_PPM(tableppm, &(tableimagew),&(tableimageh));
	glBindTexture(GL_TEXTURE_2D, tabletex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tableimagew, tableimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, tableimage);
	
	char chairppm[] = "images/chair.ppm";
	chairimage = read_PPM(chairppm, &(chairimagew),&(chairimageh));
	glBindTexture(GL_TEXTURE_2D, chairtex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, chairimagew, chairimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, chairimage);
	
	
	char legppm[] = "images/leg.ppm";
	legimage = read_PPM(legppm, &(legimagew),&(legimageh));
	glBindTexture(GL_TEXTURE_2D, legtex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, legimagew, legimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, legimage);
	
	char wallppm[] = "images/wall.ppm";
	wallimage = read_PPM(wallppm, &(wallimagew), &(wallimageh));
	glBindTexture(GL_TEXTURE_2D, walltex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallimagew, wallimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, wallimage);
	
	char ceilingppm[] = "images/ceiling.ppm";
	ceilingimage = read_PPM(ceilingppm, &(ceilingimagew), &(ceilingimageh));
	glBindTexture(GL_TEXTURE_2D, ceilingtex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ceilingimagew, ceilingimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, ceilingimage);
	
	char floorppm[] = "images/floor.ppm";
	floorimage = read_PPM(floorppm, &(floorimagew), &(floorimageh));
	glBindTexture(GL_TEXTURE_2D, floortex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorimagew, floorimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, floorimage);
	
	wall_list = createDL_wall_list();
	chair_surface_list = createDL_chair_surface_list();
	leg_list = createDL_leg_list();
}
roomModel::~roomModel() {
	
}
	
void roomModel::initTexture() {	
	
}
	
void roomModel::draw() {
	if(cameraPos == 1) {	//Set Lookat to Chair
		gluLookAt(x, y, z, xc, yc, zc, 0.0f, 1.0f, 0.0f);
	} else if(cameraPos == 2) {	//Set Lookat to table
		gluLookAt(-1.0f * x, y, z, xt, yt, zt, 0.0f, 1.0f, 0.0f);
	}
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.5f * cubesize , 0.0f);
			glScalef(2.5f, 1.0f, 2.5f);
			drawWalls();
		glPopMatrix();
		glPushMatrix();
			glPushMatrix();
				glScalef(2.0f, 2.0f, 2.0f);
				glTranslatef(xc, 0.0f, zc);
				glRotatef(90, 0.0f, 1.0f, 0.0f);
				drawChair();
			glPopMatrix();
			glPushMatrix();
				glScalef(2.3f, 2.3f, 2.3f);
				glTranslatef(xt, 0.0f, zt);
				drawTable();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
	
void roomModel::setCamera(int pos) {
	cameraPos = pos;
}
