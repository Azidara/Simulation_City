//
//  Texture_Files.cpp
//  SimulationCity
//
//  Created by Albert Bode on 1/21/15.
//  Copyright (c) 2015 Albert Bode. All rights reserved.
//
/* texture.c - by David Blythe, SGI */

/* read_texture is a simplistic routine for reading an SGI .rgb image file. */

//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Texture_Files.h"
//Cross-platform declaration.
#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
using namespace std;

#define CHECKW                    64
#define CHECKH                    64
#define CHECK_TEXTURE             0
#define NUM_TEXTURES              1




void makeCheckImage()
{
	width = CHECKW;
	height = CHECKH;
	int size = width*height*4;
	if( texels ) delete[] texels;
	texels = (GLubyte *)malloc(sizeof(GLubyte)*size);
	register int i,j,k,c;
	for (k = 0, i = 0; i < width; i++) {
		for (j = 0; j < height; j++, k+=4 ) {
			c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
			texels[k + 0] = (GLubyte) c;
			texels[k + 1] = (GLubyte) c;
			texels[k + 2] = (GLubyte) c;
			texels[k + 3] = 255;
		}
	}
}

void textSelect( int textNum ){
	
	
	textNum = 3;
	unsigned *text;
	
	switch ( textNum )
	{
		case 1:
			// Bark texture
			text = read_texture( "/Users/Albert/textureFiles/Bark.sgi", &width, &height );
			
			break;
		case 2:
			// Brick texture
			text = read_texture( "/Users/Albert/textureFiles/brick.sgi", &width, &height );
			
			break;
		case 3:
			// Grass texture
			text = read_texture( "/Users/Albert/textureFiles/grass.sgi", &width, &height );
			break;
		case 4:
			// Hardwood floor texture
			text = read_texture( "/Users/Albert/textureFiles/hardwoodfloor.sgi", &width, &height );
			break;
		case 5:
			// Marble texture
			text = read_texture( "/Users/Albert/textureFiles/marble.sgi", &width, &height );
			break;
		case 6:
			// Rock texture
			text = read_texture( "/Users/Albert/textureFiles/rocktexture.sgi", &width, &height );
			break;
		case 7:
			// Wood texture
			text = read_texture( "/Users/Albert/textureFiles/yellowWood.sgi", &width, &height );
			break;
	}
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, text );
}

static void ConvertShort(unsigned short *array, unsigned int length) {
	unsigned short b1, b2;
	unsigned char *ptr;
	
	ptr = (unsigned char *)array;
	while (length--) {
		b1 = *ptr++;
		b2 = *ptr++;
		*array++ = (b1 << 8) | (b2);
	}
}

static void ConvertUint(unsigned *array, unsigned int length) {
	unsigned int b1, b2, b3, b4;
	unsigned char *ptr;
	
	ptr = (unsigned char *)array;
	while (length--) {
		b1 = *ptr++;
		b2 = *ptr++;
		b3 = *ptr++;
		b4 = *ptr++;
		*array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
	}
}

static ImageRec *ImageOpen(char *fileName)
{
	union {
		int testWord;
		char testByte[4];
	} endianTest;
	ImageRec *image;
	int swapFlag;
	int x;
	
	endianTest.testWord = 1;
	if (endianTest.testByte[0] == 1) {
		swapFlag = 1;
	} else {
		swapFlag = 0;
	}
	
	image = (ImageRec *)malloc(sizeof(ImageRec));
	if (image == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	if ((image->file = fopen(fileName, "rb")) == NULL) {
		perror(fileName);
		exit(1);
	}
	
	fread(image, 1, 12, image->file);
	
	if (swapFlag) {
		ConvertShort(&image->imagic, 6);
	}
	
	image->tmp = (unsigned char *)malloc(image->xsize*256);
	image->tmpR = (unsigned char *)malloc(image->xsize*256);
	image->tmpG = (unsigned char *)malloc(image->xsize*256);
	image->tmpB = (unsigned char *)malloc(image->xsize*256);
	if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
		image->tmpB == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	
	if ((image->type & 0xFF00) == 0x0100) {
		x = image->ysize * image->zsize * (int) sizeof(unsigned);
		image->rowStart = (unsigned *)malloc(x);
		image->rowSize = (int *)malloc(x);
		if (image->rowStart == NULL || image->rowSize == NULL) {
			fprintf(stderr, "Out of memory!\n");
			exit(1);
		}
		image->rleEnd = 512 + (2 * x);
		fseek(image->file, 512, SEEK_SET);
		fread(image->rowStart, 1, x, image->file);
		fread(image->rowSize, 1, x, image->file);
		if (swapFlag) {
			ConvertUint(image->rowStart, x/(int) sizeof(unsigned));
			ConvertUint((unsigned *)image->rowSize, x/(int) sizeof(int));
		}
	}
	return image;
}

static void ImageClose(ImageRec *image) {
	fclose(image->file);
	free(image->tmp);
	free(image->tmpR);
	free(image->tmpG);
	free(image->tmpB);
	free(image);
}


void bwtorgba(unsigned char *b,unsigned char *l,int n) {
	while(n--) {
		l[0] = *b;
		l[1] = *b;
		l[2] = *b;
		l[3] = 0xff;
		l += 4; b++;
	}
}

void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n) {
	while(n--) {
		l[0] = r[0];
		l[1] = g[0];
		l[2] = b[0];
		l[3] = 0xff;
		l += 4; r++; g++; b++;
	}
}

void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n) {
	while(n--) {
		l[0] = r[0];
		l[1] = g[0];
		l[2] = b[0];
		l[3] = a[0];
		l += 4; r++; g++; b++; a++;
	}
}

static void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z) {
	unsigned char *iPtr, *oPtr, pixel;
	int count;
	
	if ((image->type & 0xFF00) == 0x0100) {
		fseek(image->file, (long) image->rowStart[y+z*image->ysize], SEEK_SET);
		fread(image->tmp, 1, (unsigned int)image->rowSize[y+z*image->ysize],
			  image->file);
		
		iPtr = image->tmp;
		oPtr = buf;
		for (;;) {
			pixel = *iPtr++;
			count = (int)(pixel & 0x7F);
			if (!count) {
				return;
			}
			if (pixel & 0x80) {
				while (count--) {
					*oPtr++ = *iPtr++;
				}
			} else {
				pixel = *iPtr++;
				while (count--) {
					*oPtr++ = pixel;
				}
			}
		}
	} else {
		fseek(image->file, 512+(y*image->xsize)+(z*image->xsize*image->ysize),
			  SEEK_SET);
		fread(buf, 1, image->xsize, image->file);
	}
}

unsigned *read_texture(char *name, int *width, int *height ) {
	unsigned *base, *lptr;
	unsigned char *rbuf, *gbuf, *bbuf, *abuf;
	ImageRec *image;
	int y;
	int components;
	
	image = ImageOpen(name);
	
	if(!image)
		return NULL;
	(*width)=image->xsize;
	(*height)=image->ysize;
	components=image->zsize;
	base = (unsigned *)malloc(image->xsize*image->ysize*sizeof(unsigned));
	rbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
	gbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
	bbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
	abuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
	if(!base || !rbuf || !gbuf || !bbuf)
		return NULL;
	lptr = base;
	for(y=0; y<image->ysize; y++) {
		if(image->zsize>=4) {
			ImageGetRow(image,rbuf,y,0);
			ImageGetRow(image,gbuf,y,1);
			ImageGetRow(image,bbuf,y,2);
			ImageGetRow(image,abuf,y,3);
			rgbatorgba(rbuf,gbuf,bbuf,abuf,(unsigned char *)lptr,image->xsize);
			lptr += image->xsize;
		} else if(image->zsize==3) {
			ImageGetRow(image,rbuf,y,0);
			ImageGetRow(image,gbuf,y,1);
			ImageGetRow(image,bbuf,y,2);
			rgbtorgba(rbuf,gbuf,bbuf,(unsigned char *)lptr,image->xsize);
			lptr += image->xsize;
		} else {
			ImageGetRow(image,rbuf,y,0);
			bwtorgba(rbuf,(unsigned char *)lptr,image->xsize);
			lptr += image->xsize;
		}
	}
	ImageClose(image);
	free(rbuf);
	free(gbuf);
	free(bbuf);
	free(abuf);
	
	return (unsigned *) base;
}