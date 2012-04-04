#include "hand.h"


void hand::draw_fore_finger() {
	glColor3f(0.0f,0.4f,0.2f);
	//glScalef(fingerwr,fingerlr,fingerhr);  
	glutSolidCube(forefinger);
}

void hand::draw_back_finger() {
	glColor3f(0.0f,0.5f,0.2f);
	glScalef(fingerwr,fingerlr,fingerhr);
	glutSolidCube(backfinger);
}

void hand::draw_wrist() {
	glutSolidSphere(handsoc,15,15);
}

void hand::draw_shoulder() {
	glColor3f(0.5f, 0.5, 1.0f);
	initTexture();
	glBindTexture(GL_TEXTURE_2D, shouldertex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, shoulderimagew, shoulderimageh, 0, GL_RGB, GL_UNSIGNED_BYTE, shoulderimage);	
	GLUquadricObj *quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj,GLU_TRUE);
	glEnable(GL_TEXTURE_2D);				
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	
	glBindTexture(GL_TEXTURE_2D, shouldertex);			
	gluCylinder(quadObj, handrad, handrad, handlen, 25,25);
	glDisable(GL_TEXTURE_2D);
}


GLuint hand::Gluint_fore_fingers() {
	GLuint temp;
	temp = glGenLists(1);
	glNewList(temp,GL_COMPILE);
	draw_fore_finger();
	glEndList();
	return(temp);
}

GLuint hand::Gluint_back_fingers() {
	GLuint temp;
	temp = glGenLists(1);
	glNewList(temp,GL_COMPILE);
	draw_back_finger();
	glEndList();
	return(temp);
}

GLuint hand::Gluint_wrist() {
	GLuint temp;
	temp = glGenLists(1);
	glNewList(temp,GL_COMPILE);
	draw_wrist();
	glEndList();
	return(temp);
}

GLuint hand::Gluint_shoulder() {
	GLuint temp;
	temp = glGenLists(1);
	glNewList(temp,GL_COMPILE);
	draw_shoulder();
	glEndList();
	return(temp);
}

void hand::draw_fingers(int t) {
	//t==1 means drawing right fingers else it means drawing left fingers
	glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,1.0f); // move finger to appropraiate position
		glTranslatef(handsoc*0.8 + (fingerwr*backfinger*0.5),0.0f,0.0f);  //translation wrt wrist			
		glRotatef(f[t][0][0],0.0f,1.0f,0.0f);//rotation of back finger
		glTranslatef(0.0f,0.0f,fingerhr*backfinger/2.0); //translation of back finger w.r.t its center
		glCallList(back_fingers);
		
		glTranslatef(0.0f,0.0f,fingerhr*(backfinger)/2.0);  //translate wrt backfinger
		glRotatef(f[t][0][1],0.0f,1.0f,0.0f);//rotation of fore finger			 
		glTranslatef(0.0f,0.0f,fingerhr*(forefinger)/2.0);  //translation of fore finger w.r.t its center 			
		glCallList(fore_fingers);
	glPopMatrix();
	glPushMatrix();
		glRotatef(120.0f,0.0f,0.0f,1.0f); // move finger to appropraiate position
		glTranslatef(handsoc*0.8 + (fingerwr*backfinger*0.5),0.0f,0.0f);  //translation wrt wrist			
		glRotatef(f[t][1][0],0.0f,1.0f,0.0f);//rotation of back finger
		glTranslatef(0.0f,0.0f,fingerhr*backfinger/2.0); //translation of back finger w.r.t its center
		glCallList(back_fingers);
		
		glTranslatef(0.0f,0.0f,fingerhr*(backfinger)/2.0);  //translate wrt backfinger
		glRotatef(f[t][1][1],0.0f,1.0f,0.0f);//rotation of fore finger			 
		glTranslatef(0.0f,0.0f,fingerhr*(forefinger)/2.0);  //translation of fore finger w.r.t its center 			
		glCallList(fore_fingers);
	glPopMatrix();
	glPushMatrix();
		glRotatef(240.0f,0.0f,0.0f,1.0f); // move finger to appropraiate position
		glTranslatef(handsoc*0.8 + (fingerwr*backfinger*0.5),0.0f,0.0f);  //translation wrt wrist			
		glRotatef(f[t][2][0],0.0f,1.0f,0.0f);//rotation of back finger
		glTranslatef(0.0f,0.0f,fingerhr*backfinger/2.0); //translation of back finger w.r.t its center
		glCallList(back_fingers);
		
		glTranslatef(0.0f,0.0f,fingerhr*(backfinger)/2.0);  //translate wrt backfinger
		glRotatef(f[t][2][1],0.0f,1.0f,0.0f);//rotation of fore finger			 
		glTranslatef(0.0f,0.0f,fingerhr*(forefinger)/2.0);  //translation of fore finger w.r.t its center 			
		glCallList(fore_fingers);
	glPopMatrix();	
}

void hand::draw_hand(int t) {
	//t=1 means right else left i.e. for t=0;
	
	glCallList(shoulders);	//code to draw Cylinder
	
	glTranslatef(0.0f,0.0f,handlen+handsoc);	//translate for wrist
	glColor3f(1.0f, 0.0f, 1.0f);
	glRotatef(soc[t][0],1.0f,0.0f,0.0f);
	glRotatef(soc[t][1],0.0f,1.0f,0.0f);
	glRotatef(soc[t][2],0.0f,0.0f,1.0f); //rotate for wrist
	glCallList(wrists);	//code to draw wrist
	
	//translation for fingers
	draw_fingers(t);
}

hand::hand(float bdlen) {
	bodylen = bdlen;
	initTexture();
	glGenTextures(1, texName);
	shouldertex = texName[0];
	
	f[0][0][0] = f[0][0][1] = f[0][1][0] = f[0][1][1] = f[0][2][0] = f[0][2][1] = 0.0;
	f[1][0][0] = f[1][0][1] = f[1][1][0] = f[1][1][1] = f[1][2][0] = f[1][2][1] = 0.0;
	soc[0][0] = soc[0][1] = soc[0][2] = soc[1][0] = soc[1][1] = soc[1][2] = 0.0;
	handlen = 1.6f;
	handrad = 0.15f; handsoc = 0.16f; backfinger = 0.3f; forefinger =0.3f;
	fingerwr = 0.1f; fingerlr = 0.4f; fingerhr = 1.0f;
	shoulder_ang[0] = shoulder_ang[1] = 0.0f;
	
	fore_fingers = Gluint_fore_fingers();
	back_fingers = Gluint_back_fingers();
	wrists = Gluint_wrist();
	shoulders = Gluint_shoulder();
}

void hand::initTexture() {
	char filename[] = "images/shoulder.ppm";
	shoulderimage = read_PPM(filename, &shoulderimagew, &shoulderimageh);
}

hand::~hand() {
	
}

void hand::draw() {
	glPushMatrix();
		glTranslatef(-(bodylen+handrad)/2.0,-bodylen/5.0,0.0);	//translate for drawing left hand
		glRotatef(shoulder_ang[0], 1.0, 0.0, 0.0);	//rotate for left hand
		draw_hand(0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef((bodylen+handrad)/2.0,-bodylen/5.0,0.0);	//translate for drawing right hand
		glRotatef(shoulder_ang[1], 1.0, 0.0, 0.0);	//rotate for right hand
		draw_hand(1);
	glPopMatrix();
}
	
void hand::rotate_finger(int lr, int fno, int ul, int i) {
	if(i==1 && f[lr][fno][ul] < 45.0f) {
		f[lr][fno][ul] += 1.5f;
	} else if(f[lr][fno][ul]>-45.0f) {
		f[lr][fno][ul] -= 1.5f;
	}
}	//lr->left(0), right(1) : fno->finger no(1,2,3)	:	ul->upper, lower

void hand::rotate_wrist(int lr, int a, int i) {
	if(i==1 && (soc[lr][a] < 45.0f || a == 2)) {
		soc[lr][a] += 1.5f;
	} else if(soc[lr][a]>-45.0f || a==2) {
		soc[lr][a] -= 1.5f;
	}
}
void hand::rotate_shoulder(int lr,int i){
	if(i == 1) shoulder_ang[lr]+= 1.5f;
	else if(i==-1) shoulder_ang[lr] -= 1.5f;
}

GLubyte* hand::read_PPM(char* filename, int* width, int* height)
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
