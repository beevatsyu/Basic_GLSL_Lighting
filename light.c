/* Basic GLSL Lighting
 * Author: Partha Bera
 * To compile: gcc light.c -lGL -lGLU -lGLEW -lglut
 * To run: ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

GLuint v,f,p,window;
GLfloat angle = 0.0;
GLfloat lx = 1.0, ly = 1.0, lz = 1.0, lw = 0.0;

char *textFileRead(char *fn) {
	FILE *fp;
	char *content = NULL;
	int count = 0;

	if (fn != NULL) {
		fp = fopen(fn, "rt");

		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) {
				content = malloc(sizeof (char) * (count + 1));
				count = fread(content, sizeof (char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

void printShaderInfoLog(GLuint obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("Shader Info Log: %s\n", infoLog);
		free(infoLog);
	} else {
		printf("Shader Info Log: OK\n");
	}
}

void printProgramInfoLog(GLuint obj) {
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0) {
		infoLog = (char *) malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("Program Info Log: %s\n", infoLog);
		free(infoLog);
	} else {
		printf("Program Info Log: OK\n");
	}
}

void init(void)
{
	printf("OpenGL Vendor: %s\n",(char*) glGetString(GL_VENDOR));
	printf("OpenGL Renderer: %s\n",(char*) glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n\n",(char*) glGetString(GL_VERSION));

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mat_diffuse_gold[] = { 201.0/255.0, 201.0/255.0, 9.0/255.0, 1.0 };
	//GLfloat mat_diffuse_silver[] = { 246.0/255.0, 249.0/255.0, 249.0/255.0, 1.0 };
	//GLfloat mat_diffuse_copper[] = { 184.0/255.0, 115.0/255.0, 51.0/255.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat light_position[] = { lx, ly, lz, lw };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_gold);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glPushMatrix();
	//glutSolidSphere(1.0, 20, 16);
	glRotatef(angle, 1, 1, 1);
	glutSolidTeapot(0.8);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
			1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
			1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			glutDestroyWindow(window);
			exit(0);
			//Light navigation
		case 'l':
			lx += 0.1;
			glutPostRedisplay();
			break;
		case 'j':
			lx -= 0.1;
			glutPostRedisplay();
			break;
		case 'i':
			ly += 0.1;
			glutPostRedisplay();
			break;
		case 'k':
			ly -= 0.1;
			glutPostRedisplay();
			break;
		case 'o':
			lz += 0.1;
			glutPostRedisplay();
			break;
		case 'u':
			lz -= 0.1;
			glutPostRedisplay();
			break;
	}
}

void idle()
{
	//printf("angle: %f\n",angle);
	if(angle > 360.0) angle = fmod(angle,360.0);
	angle += 0.1;
	glutPostRedisplay();
}

void setShaders() 
{
	char *vs, *fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("pfdsl.vert");
	fs = textFileRead("pfdsl.frag");

	const char * ff = fs;
	const char * vv = vs;

	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);

	free(vs);
	free(fs);

	glCompileShader(v);
	glCompileShader(f);

	p = glCreateProgram();

	glAttachShader(p, v);
	glAttachShader(p, f);

	glLinkProgram(p);
	glUseProgram(p);

	printShaderInfoLog(v);
	printShaderInfoLog(f);

	printProgramInfoLog(p);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	window = glutCreateWindow("Basic GLSL Lighting");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutFullScreen();

	GLenum status = glewInit();
	if( status!= GLEW_OK)
	{
		printf("Error: %s\n",glewGetErrorString(status));
		exit(1);
	}

	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	setShaders();

	glutMainLoop();

	return 0;
}
