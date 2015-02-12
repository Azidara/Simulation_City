//
//  Initialization_Files.cpp
//  SimulationCity
//
//  Created by Albert Bode on 1/16/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//

#include <iostream>
#include <vector>
//Cross-platform declaration.
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Initialization_Files.h"
#include "Objects.h"
#include "Texture_Files.h"
#include "MenuDrawFuncs.h"
using namespace std;

#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];

extern objects::customButton start,option,changelog,quit;
void myInit()
{
	// Background color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	start.readFile(1);
	option.readFile(1);
	changelog.readFile(1);
	quit.readFile(1);
	
	currentMenu = 1;
	
	aspect = resHeight/resWidth;
	
	// 2D world projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.01, 1000.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef(0, 0, -25);
	glEnable( GL_DEPTH_TEST );
	
	// Texture generation
	makeCheckImage();
 
	// Texture object creation
	glGenTextures( NUM_TEXTURES, texName );
 
	// Texture specification
	glBindTexture( GL_TEXTURE_2D, texName[CHECK_TEXTURE] );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels );
}

void MainDraw(){
	switch (currentMenu){
		case 1:
			MainMenuDraw();
			break;
		case 2:
			OptionsMenuDraw();
			break;
	}
}

