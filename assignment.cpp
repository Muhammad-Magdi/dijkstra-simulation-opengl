// shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.

//#include "pch.h"
#include <bits/stdc++.h>
#include "polygon.h"

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

polygon* a = new polygon(15, mp(0,0), 0.1);
polygon* g = new polygon(15, mp(0,0), 0.05);
point startNode = mp(0, 0);
point cur_target;
bool starting = 0;

// helper funtions
float distance(point a, point b);

// interrupt functions
void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);

// drawing functions
void addNode();
void drawPath();
void initRendering();
void tryThis();

void timer(int);

int main(int argc, char** argv) {
	nodes[0] = mp(0,  0);
	nodes[1] = mp(1,  1);
	nodes[2] = mp(1, -1);
	nodes[3] = mp(4,  2);

	arr[0].pb(1);arr[0].pb(2);
	arr[1].pb(3);

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size

	//Create the window
	glutCreateWindow("Basic Shapes");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(tryThis);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(0, timer, 0);

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}

void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
		(double)w / (double)h, //The width-to-height ratio
		1.0,                   //The near z clipping coordinate
		200.0);                //The far z clipping coordinate
}


void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	glutPostRedisplay();
	switch (key){
		case GLUT_KEY_UP: // 'E'
			printf("UP");
			if(path.size())return;
			// fill path vector with the output of dijkstra
			path.pb(0);
			path.pb(1);
			path.pb(3);
			// startNode = first node in path
			startNode = nodes[*(path.begin())];
			// remove first node in path
			path.erase(path.begin());
			break;
		case 27: //Escape key
			printf("escape\n");
			exit(0); //Exit the program
			break;
	}
}

void timer(int){
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
	if(path.size() == 0) return;
	float slope = (cur_target.Y - startNode.Y) / (cur_target.X - startNode.X);
	float U = (cur_target.X - startNode.X);
	float D = (cur_target.Y - startNode.Y);
	float L = distance(cur_target, startNode);
	startNode.X += U * 0.1 / L;
	startNode.Y += D * 0.1 / L;
	printf("%f %f\n", startNode.X, startNode.Y);
}

float distance(point a, point b){
	return sqrt((a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y));
}

void drawPath(){
	if(path.size() == 0)return;
	cur_target = nodes[*(path.begin())];
	if(distance(cur_target, startNode) <= 0.1){
		startNode = cur_target;
		path.erase(path.begin());
	}
	glPushMatrix();
	glTranslatef(startNode.X, startNode.Y, -9.5);
	glColor3f(0.0, 1.0, 0.0);
	g->draw();
	glPopMatrix();
}

void tryThis(){
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	// draw graph nodes
	for(auto node: nodes){
		glPushMatrix();
		glColor3f(1.0,1.0,0.0);
		glTranslatef(node.Y.X, node.Y.Y, 0.0);
		a->draw();
		glPopMatrix();
	}

	// draw graph edges
	for(int i = 0;i < 4;i++)
		for(auto child :arr[i]){
			glPushMatrix();
			glColor3f(1.0,0.0,0.0);
			glBegin(GL_LINES);
			glVertex3f(nodes[i].X, nodes[i].Y, -10.0);
			glVertex3f(nodes[child].X, nodes[child].Y, -10.0);
			glEnd();
			glPopMatrix();
		}

	// draw path
	drawPath();

	// draw grid
	glPushMatrix();
	glBegin(GL_LINES);
	glLineWidth(0.1);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-4.0, 0.0, -10.0);glVertex3f(4.0, 0, -10.0);
	glVertex3f(-4.0, -1.0, -10.0);glVertex3f(4.0, -1.0, -10.0);
	glVertex3f(-4.0, 1.0, -10.0);glVertex3f(4.0, 1.0, -10.0);
	glVertex3f(-4.0, -2.0, -10.0);glVertex3f(4.0, -2.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.0);glVertex3f(4.0, 2.0, -10.0);
	glVertex3f(-4.0, -3.0, -10.0);glVertex3f(4.0, -3.0, -10.0);
	glVertex3f(-4.0, 3.0, -10.0);glVertex3f(4.0, 3.0, -10.0);

	glVertex3f(0.0, -4.0, -10.0);glVertex3f(0.0, 4.0, -10.0);
	glVertex3f(1.0, -4.0, -10.0);glVertex3f(1.0, 4.0, -10.0);
	glVertex3f(-1.0, -4.0, -10.0);glVertex3f(-1.0, 4.0, -10.0);
	glVertex3f(2.0, -4.0, -10.0);glVertex3f(2.0, 4.0, -10.0);
	glVertex3f(-2.0, -4.0, -10.0);glVertex3f(-2.0, 4.0, -10.0);
	glVertex3f(3.0, -4.0, -10.0);glVertex3f(3.0, 4.0, -10.0);
	glVertex3f(-3.0, -4.0, -10.0);glVertex3f(-3.0, 4.0, -10.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers(); //Send the 3D scene to the screen
}
