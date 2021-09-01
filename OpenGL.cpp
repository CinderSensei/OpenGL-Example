/*  For Linux
	Compile with g++ OpenGL.cpp -lglut -lGLU -lGL 
	Run ./a.out
	Ubuntu subSystem and xMing used.

	Implemented in C++ using glut lib
*/

#include <GL/glut.h>
#include <stdio.h>  
#include <math.h> 


float r = 0.0;
float angle=0.0;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=10.0f;

float x2=-1.0f,y2=2.5f,z2=1.5f;
float x3=-1.0f,y3=1.5f,z3=1.5f;
float x4=-1.0f,y4=2.0f,z4=2.05f;
float x5=-1.0f,y5=0.55f,z5=1.1f;
float x6=2.0f,y6=0.35f,z6=1.55f;  
void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.2f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.1f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.1f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}
void keyboard2(GLubyte key, GLint xmouse, GLint ymouse){ 
			switch (key){
				case 'i': {
					x2+=0.1f;
					x3+=0.1f;
					x4+=0.1f;
					x5+=0.1f;
					
					break;
				}
				case 'm': {
					x2-=0.1f;
					x3-=0.1f;
					x4-=0.1f;
					x5-=0.1f;
					
					break;
				}
				case 'k': {
					z2+=0.1f;
					z3+=0.1f;
					z4+=0.1f;
					z5+=0.1f;
					
					break;
				}
				case 'j': {
					z2-=0.1f;
					z3-=0.1f;
					z4-=0.1f;
					z5-=0.1f;
					
					break;
				}


			}
		
	}

void changeSize(int w, int h) {

	
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	
	glMatrixMode(GL_PROJECTION);

	
	glLoadIdentity();

	
	glViewport(0, 0, w, h);

	
	gluPerspective(45,ratio,1,100);

	glMatrixMode(GL_MODELVIEW);
}

void drawHead(){ // drawing the robot's head with sphere.Also wireframe version is showed as a reflection of a solid object.
	glPushMatrix();

	glColor3ub(128, 0, 128);
	glTranslatef(x2, y2, z2);
	
	glutSolidSphere(0.3f,20,20);

	glPopMatrix();
}

void drawBody(){ // drawing the robot's body with 2 cubes. Also wireframe version is showed as a reflection of a solid object.
	glPushMatrix();

	glColor3ub(255, 69, 0);
	glTranslatef(x3 ,y3, z3);
	glutSolidCube(0.8f);
	glTranslatef(0.0f, 0.3f, 0.0f);
	glutSolidCube(0.8f);
	
	glPopMatrix();
	
}



void drawArmsSolid(){ // same but solid
	glPushMatrix();
	glColor3ub(128, 0, 128);
	
	glTranslatef(x4, y4, z4);
	glRotatef(135, 0.0f, 0.0f, 1.0f);

	glutSolidCube(0.25f);
	
	for(int i = 0; i < 5; i++){
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutSolidCube(0.25f);
	}
    glPopMatrix();

    glPushMatrix();
	glTranslatef(x4, y4, z4-1.10f);
	glRotatef(135, 0.0f, 0.0f, 1.0f);
	glutSolidCube(0.25f);

	for(int i = 0; i < 5; i++){
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutSolidCube(0.25f);
	}
	
	glPopMatrix();
}



void drawWheelSolid(){ // wheel is created with glucylinder.
	glPushMatrix();
	glColor3ub(255,0,0);
	glTranslatef(x5, y5, z5);
	gluCylinder(gluNewQuadric(),0.55f,0.55f,0.8f,100,10);
	glPopMatrix();
}

void drawRobot() { // robot is created here.

	drawHead();
	
	drawBody();
	
	
	drawArmsSolid();

	
	drawWheelSolid();

}

void drawGrounds(void){ // drawing the ground as lime green, and drawing background there is 1 background for now.
	glColor3ub(0, 255, 0);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	glColor3ub(230, 250, 250);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, -100.0f, -100.0f);
		glVertex3f(-100.0f, 100.0f,  0.0f);
		glVertex3f( 100.0f, 100.0f,  0.0f);
		glVertex3f( 100.0f, -100.0f, -100.0f);
	glEnd();
}


void drawBall(){ // drawing the solid ball with sphere.
	glPushMatrix();
	glColor3ub(0, 255, 255);
	if(x6>-0.9f){ 
		x6 -= 0.005f;
	}
	else{ 
		x6 = 2.0f;
	}
	glTranslatef(x6, y6, z6);
	glutSolidSphere(0.4f,20,20);
	glPopMatrix();
}

void collission(){
	float d = sqrt(pow(x5-x6,2) + pow(x5+0.275f,2));
	float d2 = sqrt(pow(z5-z6,2) + pow(z5+0.275f,2));
	if(d<0.4f || d2<0.4f){
		x2= -1.0f;
		x3= -1.0f;
		x4= -1.0f;
		x5 = -1.0f;
	}
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glLoadIdentity();
	
	gluLookAt(	x, 1.5f, z,  
			x+lx, 1.5f,  z+lz,
			0.0f, 1.5f,  0.0f);
		// camera arrangement, use arrow keys to look around
        
	drawGrounds();
	glTranslatef(0.0,0,0.0);

	drawRobot();
	drawBall();
	collission();


	glutSwapBuffers();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("OpenGL");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keyboard2);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}

