#include<stdio.h>
#include"main.h"

void drawDanishFlag(unsigned char * dest){
    for(int i = 0; i < HEIGHT; ++i){
            if(i<5*HEIGHT/12||i>7*HEIGHT/12){
            for(int j = 0; j < WIDTH; ++j){
                if(j<5*WIDTH/17||j>7*WIDTH/17){
                    putPixel(dest,j,i,0xff,0,0);
                }
            }
        }
    }
}

void drawChineseFlag(unsigned char * dest){
    drawRect(dest,0,0,WIDTH,HEIGHT,255,0,0);
    drawStarN(dest,5,0,5*WIDTH/32,3*HEIGHT/4,80,255,255,0,200);
    drawStarN(dest,5,0.5,3*WIDTH/8,16*HEIGHT/18,20,255,255,0,7.9);
    drawStarN(dest,5,0.5,13*WIDTH/32,13*HEIGHT/18,20,255,255,0,7.9);
    drawStarN(dest,5,0,4*WIDTH/11,4*HEIGHT/7,20,255,255,0,7.9);
    drawStarN(dest,5,0,6*WIDTH/21,5*HEIGHT/11,20,255,255,0,7.9);
}

void drawJapaneseFlag(unsigned char * dest){
    drawCircle(dest, WIDTH/2, HEIGHT/2, 120.0f, 255, 0, 0, 2.5f);
}

void drawAmericanFlag(unsigned char * dest){
    //seven red lines, 6 white
    for(int i = 0; i < 13; ++i){
        if(i%2==0){
            drawRect(dest,0,i*HEIGHT/13,WIDTH,(i+1)*HEIGHT/13,255,0,0);
        }
    }
    drawRect(dest,0,6*HEIGHT/13,6*WIDTH/13,HEIGHT,0,0,255);
    //drawStarN(dest,5,380,350,200.0f,0,255,0,0.8f);
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 6-(i&1); ++j){
            drawStarN(dest,5,0.0f,WIDTH/25+j*WIDTH/13+(i&1)*WIDTH/26,25*HEIGHT/26-i*HEIGHT/18,10.0f,255,255,255,4.9f);
        }
    }
}

void drawUKFlag(unsigned char * dest){
    drawRect(dest,0,0,WIDTH,HEIGHT,0,0,127);

    drawLine(dest,40,0,0,WIDTH,HEIGHT,255,255,255,2);
    drawLine(dest,40,0,HEIGHT,WIDTH,0,255,255,255,2);
    drawLine(dest,13,0,-3*HEIGHT/80,WIDTH/2,37*HEIGHT/80,255,0,0,2);
    drawLine(dest,13,WIDTH/2,43*HEIGHT/80,WIDTH,83*HEIGHT/80,255,0,0,2);
    drawLine(dest,13,0,77*HEIGHT/80,WIDTH/2,37*HEIGHT/80,255,0,0,2);
    drawLine(dest,13,WIDTH/2,43*HEIGHT/80,WIDTH,3*HEIGHT/80,255,0,0,2);

    drawRect(dest,6*WIDTH/14,0,8*WIDTH/14,HEIGHT,255,255,255);
    drawRect(dest,0,6*HEIGHT/14,WIDTH,8*HEIGHT/14,255,255,255);
    drawRect(dest,6*WIDTH/13,0,7*WIDTH/13,HEIGHT,255,0,0);
    drawRect(dest,0,6*HEIGHT/13,WIDTH,7*HEIGHT/13,255,0,0);
}
