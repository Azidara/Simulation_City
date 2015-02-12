//
//  Objects.h
//  SimulationCity
//
//  Created by Albert Bode on 1/16/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//

#ifndef __SimulationCity__Objects__
#define __SimulationCity__Objects__

#include <stdio.h>
#include <vector>

using namespace std;

class GlutPt3D{
public:
	float x,y,z;
};

class wcPt3D{
public:
	float x,y,z;
	
	void wc3DtoGl3D();
	void Gl3Dtowc3D();
};

class object{
	public:
		GlutPt3D center;
		
		virtual void readFile(int id) = 0;
		virtual void readTexture(int id) = 0;
		virtual void drawObject(float x, float y, float z, int name) = 0;
};

namespace objects
{
	class customButton : public object{
		vector<GlutPt3D> shape;
		float meshSize, textureSize;
		
	public:
		virtual void readFile(int id);
		virtual void readTexture(int id);
		virtual void drawObject(float x, float y, float z, int name);
		
		customButton(){
			meshSize = 2.0;
		}
	};
};



#endif /* defined(__SimulationCity__Objects__) */
