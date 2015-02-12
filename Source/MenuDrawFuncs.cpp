//
//  Options_Menu.cpp
//  SimulationCity
//
//  Created by Albert Bode on 1/21/15.
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
#include "MenuDrawFuncs.h"
#include "Objects.h"


objects::customButton resolution,framerate,mainMenu,textureQuality;

void OptionsMenuDraw(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	resolution.readFile(2);

	
	// Resoulution
	resolution.drawObject(0, 1, 0, resolutionbutton);
	
	// Texture Quality
	
	
	// Framerate

	
	// Back to Main Menu
	
	
	glutSwapBuffers();
}

objects::customButton start,option,changelog,quit;

void MainMenuDraw(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	
	// Texture enabling
	//glEnable( GL_TEXTURE_2D );
	//glBindTexture( GL_TEXTURE_2D, texName[CHECK_TEXTURE] );
	
	// glPushMatrix();
	start.drawObject(-7,-0.4,0, startbutton);
	// glPopMatrix();
	// glPushMatrix();
	option.drawObject(-7, -2.6, 0, optionbutton);
	// glPopMatrix();
	// glPushMatrix();
	changelog.drawObject(-7,-4.8,0, changelogbutton);
	// glPopMatrix();
	// glPushMatrix();
	quit.drawObject(-7, -7, 0, quitbutton);
	// glPopMatrix();
	
	glutSwapBuffers();
}