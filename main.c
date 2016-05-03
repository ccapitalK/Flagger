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
void buildBitmap(char * file_name, int flag_no);
void printFlagList();

typedef struct {
    const char * name;
    const char * description;
    void (*func)(unsigned char * dest);
} flag_entry;

flag_entry FLAG_TABLE[] = {
    { "US", "American Flag", &drawAmericanFlag },
    { "DN", "Danish Flag",   &drawDanishFlag   },
    { "JP", "Japanese Flag", &drawJapaneseFlag },
};

int main(int argc, char * argv[]) {
    char * file_name="./flag.bmp";
    if(argc<2){
        printf("Usage: [flagger] flagname [--help] [-o Output.bmp]\n");
        exit(EXIT_FAILURE);
    }
    if(strcmp(argv[1],"--help")==0){
        printFlagList();
        exit(EXIT_SUCCESS);
    }
    buildBitmap(file_name, 0);
    return EXIT_SUCCESS;
}

void printFlagList(){
    printf("\nFlag Codes:\n    [Code]:   [Description]\n");
    for(unsigned int i = 0; i < sizeof(FLAG_TABLE)/sizeof(flag_entry); ++i){
        printf("    %-6s:   %s\n", FLAG_TABLE[i].name, FLAG_TABLE[i].description);
    }
}

void buildBitmap(char * file_name, int flag_no){
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
    FILE * targetFile = fopen(file_name,"w");
    if(targetFile==NULL){
        perror("Could not open file for writing");
        exit(EXIT_FAILURE);
    }

    makeBMPHeader(bmpHeader);
    makeDIBHeader(DIBHeader);
    switch(flag_no) {
        case 0:
            drawDanishFlag(screen);
            break;
        case 1:
            drawJapaneseFlag(screen);
            break;
        case 2:
            drawAmericanFlag(screen);
            break;
    }

    writeBMPHeader(targetFile,bmpHeader);
    writeDIBHeader(targetFile,DIBHeader);
    writePixelArray(targetFile,screen);
    fclose(targetFile);
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
