//Sahan Fernando 'u/sahanfernando' <z5113187@zmail.unsw.edu.au>
//TUT5261       Tutor: Hayden
//2015-03-23
//To make a bmp file containing a Danish flag
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"main.h"

int WIDTH=680;
int HEIGHT=480;
//draw the danish flag using the putPixel() function
void drawDanishFlag(unsigned char * dest);
void drawJapaneseFlag(unsigned char * dest);
void drawAmericanFlag(unsigned char * dest);

int main(int argc, char * argv[]) {
    FILE * targetFile = NULL;
    unsigned char bmpHeader[BMPHEADERSIZE];
    unsigned char DIBHeader[DIBHEADERSIZE];
    unsigned char screen[WIDTH*HEIGHT*3];
    for(int i = 0; i < WIDTH*HEIGHT*3; ++i){
        if(i<BMPHEADERSIZE){
            bmpHeader[i]=0;
        }
        if(i<DIBHEADERSIZE){
            DIBHeader[i]=0;
        }
        screen[i]=0xff;
    }
    targetFile=fopen("./Flag.bmp","w");

    makeBMPHeader(bmpHeader);
    makeDIBHeader(DIBHeader);
    //drawDanishFlag(screen);
    //drawJapaneseFlag(screen);
    drawAmericanFlag(screen);

    writeBMPHeader(targetFile,bmpHeader);
    writeDIBHeader(targetFile,DIBHeader);
    writePixelArray(targetFile,screen);
    fclose(targetFile);
    return EXIT_SUCCESS;
}

void writeDIBHeader(FILE* dest,  unsigned char * header){
    for(int i = 0; i < DIBHEADERSIZE; ++i){
        fprintf(dest,"%c",header[i]);
    }
}

void writeBMPHeader(FILE* dest,  unsigned char * header){
    for(int i = 0; i < BMPHEADERSIZE; ++i){
        fprintf(dest,"%c",header[i]);
    }
}

void writePixelArray(FILE* dest, unsigned char * data){
    for(int i = 0; i < WIDTH*HEIGHT*3; ++i){
        fprintf(dest,"%c",data[i]);
    }
}

void makeBMPHeader(unsigned char * header){
    header[0]='B';
    header[1]='M';
    unsigned int fileSize = BMPHEADERSIZE+DIBHEADERSIZE+WIDTH*HEIGHT*3;
    memcpy(&header[2],&fileSize,4);
    unsigned int dataOffset = BMPHEADERSIZE+DIBHEADERSIZE;
    memcpy(&header[10],&dataOffset,4);
}

void makeDIBHeader(unsigned char * header){
    unsigned int first3Fields[]={DIBHEADERSIZE, WIDTH, HEIGHT};
    memcpy(header,first3Fields,3*4);
    header[12]=1;
    header[14]=24;
    unsigned int imageSize=WIDTH*HEIGHT*3;
    memcpy(&header[20],&imageSize,4);
    //not entirely sure what exactly this field does, seems to DPI value
    unsigned int resolution=0x0b13; 
    memcpy(&header[24],&resolution,4);
    memcpy(&header[28],&resolution,4);
}
