//
//  File_IO.cpp
//  SimulationCity
//
//  Created by Albert Bode on 1/21/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//
#include <iostream>
#include <fstream>
//OpenGl declaration.
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Objects.h"

string findPath(char *argv){

    string ExePath(argv);

    //cout << "ExePath is " << ExePath << endl;

    while ((ExePath.size() > 0) && ((ExePath[ExePath.size()-1]!='\\') && (ExePath[ExePath.size()-1]!='/'))) {
            ExePath.resize(ExePath.size()-1);

    //cout << "ExePath is " << ExePath << endl;
    }

    return ExePath;
}

void objects::customButton::readFile(int id){
	fstream in;
	switch (id)
	{
		case 1:
			in.open( "/Users/Albert/objectFiles/MainButton.obj", ios::in );
			break;
		case 2:
			in.open( "/Users/Albert/objectFiles/ResolutionButton.obj", ios::in );
			break;
	}
	// Read and store the points
	string testtype;

	GlutPt3D temp;

	while ( in.eof() == false ){
		in >> testtype;

		if ( testtype == "v" ){
			in >> temp.x;
			in >> temp.y;
			in >> temp.z;
			shape.push_back( temp );
		}
	}
	// Close the file
	in.close();
}

void objects::customButton::readTexture(int id){

}

void objects::customButton::drawObject(float x, float y, float z, int name){
	center.x = x;
	center.y = y;
	center.z = z;
	glLoadName( name );
	glBegin( GL_POLYGON );
	for (int i=0;i < shape.size(); i++){
		x = center.x + (shape[i].x * meshSize);
		y = center.y + (shape[i].y * meshSize);
		z = center.z + (shape[i].z * meshSize);
		glVertex3f( x, y, z );
	}
	x = center.x + (shape[0].x * meshSize);
	y = center.y + (shape[0].y * meshSize);
	z = center.z + (shape[0].z * meshSize);
	glVertex3f( x, y, z );
	glEnd();
}
