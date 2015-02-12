//
//  main.cpp
//  SimulationCity
//
//  Created by Albert Bode on 1/16/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
//OpenGl declaration.
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Initialization_Files.h"
#include "Objects.h"
#include "MenuDrawFuncs.h"
#include "Texture_Files.h"

#define SELECT_BUFSIZE  10

// Projection parameters
float fov = 45.0;
float nearClip = 0.01;
float farClip = 10000.0;
float resHeight = 480;
float resWidth = 640;
float aspect;
int currentMenu;
void makeCheckImage();
GLubyte *texels;
GLuint texName[NUM_TEXTURES];
int width,height;

//Keyboard callbacks
void keyboard( unsigned char key, int x, int y ){
	// Process keys
	switch (key)
	{
		case 'q':
			// exit program
			exit (1);
			break;
		case 'h':
			// change resoultion
			resHeight -= 10;
			break;
		case 'H':
			// change resoultion
			resHeight += 10;
			break;
	}
	glutReshapeWindow( resWidth, resHeight );
	glutPostRedisplay();
}

// Mouse press callback
void mousePress( int button, int state, int x, int y )
{
	GLfloat inputX = x;
	GLfloat inputY = y;
	
	// Pick objects if left button down
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
		
		GLuint selectBuffer[ SELECT_BUFSIZE ];     // selections
		GLuint *ptr, names;
		int hits, i, j;
		
		// Viewport information
		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
	 
		// Selection mode
		glSelectBuffer( SELECT_BUFSIZE, selectBuffer );
		glRenderMode( GL_SELECT );
	 
		// Initialize name stack
		glInitNames();
		glPushName(-1);
	 
		// Save transformation matrix
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
	 
		// Save original projection (viewing volume)
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
	 
		// New picking viewing volume (area == 5 pixels)
		glLoadIdentity();
		gluPickMatrix ( GLdouble( inputX ),GLdouble( viewport[3] - inputY ),5.0, 5.0, viewport);
		gluPerspective( fov, aspect, nearClip, farClip );
	 
		// Draw scene
		MainDraw();
	 
		// Restore original projection (viewing volume)
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
	 
		// Restore original modelview matrix
		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();
	 
		// Swap buffers
		//glutSwapBuffers();
	 
		// End select mode
		hits = glRenderMode( GL_RENDER );
		if (hits != 0 && (selectBuffer[3] == startbutton)){
			
		}
		else if (hits > 0 && (selectBuffer[3] == optionbutton)){
			currentMenu = 2;
		}
		else if (hits > 0 && (selectBuffer[3] == changelogbutton)){

		}
		else if (hits > 0 && (selectBuffer[3] == quitbutton)){
			exit(1);
		}
		else if (hits > 0 && (selectBuffer[3] == resolutionbutton)){
			currentMenu = 1;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glutPostRedisplay();
	}
}


// Menu callback
void menu( int value )
{
	switch( value )
	{
		case 1:{
			// exit program
			exit(1);
			break;
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Initialize window system
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( resWidth, resHeight );
	glutCreateWindow( "Simcity Project" );
	
	myInit();
	
	glutDisplayFunc( MainDraw );
	
	// Input callbacks
	glutKeyboardFunc( keyboard );
	
	// Mouse press callback
	glutMouseFunc( mousePress );
	
	// Main menu
	glutCreateMenu( menu );
	glutAddMenuEntry( "Quit", 1 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );
	
	//Main event loop
	glutMainLoop();
	
}
