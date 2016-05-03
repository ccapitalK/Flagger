#include<stdio.h>
#pragma once
#define BMPHEADERSIZE 14
#define DIBHEADERSIZE 40
//these 3 are all essentially functions
#define MIN(a,b) (a<b ? a : b) //return the smaller value of parameters
#define MAX(a,b) (a>b ? a : b) //return the larger value of parameters
#define CLAMP(a,c,b) MIN(b,MAX(a,c))
//CLAMP returns c if a<=c<=b, a if c<a, or b if b<c

//write values in arrays to file
void writeBMPHeader(FILE* dest,  unsigned char * header);
void writeDIBHeader(FILE* dest,  unsigned char * header);
void writePixelArray(FILE* dest, unsigned char * data);
//fill arrays with relevant values
void makeBMPHeader(unsigned char * header);
void makeDIBHeader(unsigned char * header);
//draw the danish flag using the putPixel() function
void drawDanishFlag(unsigned char * dest);
void drawJapaneseFlag(unsigned char * dest);
void drawChineseFlag(unsigned char * dest);
void drawAmericanFlag(unsigned char * dest);
//place a pixel onto the screen array at (x,y)
void putPixel(unsigned char * dest, int x, int y, unsigned char R,
              unsigned char G, unsigned char B);
void putPixelAlpha(unsigned char * dest, int x, int y, unsigned char R,
              unsigned char G, unsigned char B, double alpha);
void drawCircle(unsigned char * dest, double x0, 
    double y0, double radius, char R, char G, char B, double smoothv);
void drawStar(unsigned char * dest, double rot, double x0, 
    double y0, double scale, char R, char G, char B, double smoothv);
void drawStarN(unsigned char * dest, int n, double rot, double x0, 
    double y0, double scale, char R, char G, char B, double smoothv);
void drawRect(unsigned char * dest, double x0, 
    double y0, double x1, double y1, char R, char G, char B);

extern int WIDTH;
extern int HEIGHT;
