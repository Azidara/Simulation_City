//
//  Texture_Files.h
//  SimulationCity
//
//  Created by Albert Bode on 1/21/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//

#ifndef __SimulationCity__Texture_Files__
#define __SimulationCity__Texture_Files__

#define CHECKW                    64
#define CHECKH                    64
#define CHECK_TEXTURE             0
#define NUM_TEXTURES              1


#include <stdio.h>
//Cross-platform declaration.
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

typedef struct _ImageRec {
	unsigned short imagic;
	unsigned short type;
	unsigned short dim;
	unsigned short xsize, ysize, zsize;
	unsigned int min, max;
	unsigned int wasteBytes;
	char name[80];
	unsigned long colorMap;
	FILE *file;
	unsigned char *tmp, *tmpR, *tmpG, *tmpB;
	unsigned long rleEnd;
	unsigned int *rowStart;
	int *rowSize;
} ImageRec;


void textSelect( int textNum );
static ImageRec *ImageOpen(char *fileName);
static void ImageClose(ImageRec *image);
unsigned *read_texture(char *name, int *width, int *height );
static void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z);
void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n);
void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n);
void bwtorgba(unsigned char *b,unsigned char *l,int n);
static void ImageClose(ImageRec *image);
static void ConvertUint(unsigned *array, unsigned int length);
static void ConvertShort(unsigned short *array, unsigned int length);
void makeCheckImage();

extern ImageRec *currentTexture;
extern int width,height;
extern int textNum;
extern GLubyte *texels;
extern GLuint texName[NUM_TEXTURES];


#endif /* defined(__SimulationCity__Texture_Files__) */
