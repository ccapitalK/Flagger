#include"main.h"
#include<math.h>

void putPixel(unsigned char * dest, int x, int y, unsigned char R,
              unsigned char G, unsigned char B){
    if(x>=0&&x<WIDTH&&y>=0&&y<HEIGHT){
        dest[3*WIDTH*y+3*x+0]=B;   
        dest[3*WIDTH*y+3*x+1]=G;   
        dest[3*WIDTH*y+3*x+2]=R;   
    }
}

void putPixelAlpha(unsigned char * dest, int x, int y, unsigned char R,
              unsigned char G, unsigned char B, double alpha){
    if(x>=0&&x<WIDTH&&y>=0&&y<HEIGHT){
        dest[3*WIDTH*y+3*x+0]=dest[3*WIDTH*y+3*x+0]*(1.0f-alpha)+B*alpha;
        dest[3*WIDTH*y+3*x+1]=dest[3*WIDTH*y+3*x+1]*(1.0f-alpha)+G*alpha;
        dest[3*WIDTH*y+3*x+2]=dest[3*WIDTH*y+3*x+2]*(1.0f-alpha)+R*alpha;
    }
}

void drawCircle(unsigned char * dest, double x0, 
    double y0, double radius, char R, char G, char B, double smoothv){
    double x, y;
    for(int i = MAX(y0-radius*1.1f,0); i < MIN(y0+radius*1.1f,HEIGHT); ++i){
        for(int j = MAX(x0-radius*1.1f,0); j < MIN(x0+radius*1.1f,WIDTH); ++j){
            x=j-x0;
            y=i-y0;
            //used for primitive anti-aliasing
            double alpha=CLAMP(0,
                    -(x*x+y*y-radius*radius)/(255.0f*smoothv),1.0);
            putPixelAlpha(dest,j,i,R,G,B,alpha);
        }
    }
}

void drawRect(unsigned char * dest, double x0, 
    double y0, double x1, double y1, char R, char G, char B){
    for(int i = y0; i < y1; ++i){
        for(int j = x0; j < x1; ++j){
            putPixel(dest,j,i,R,G,B);
        }
    }
}

void drawLine(unsigned char * dest, double thickness, double x0, double y0,
        double x1, double y1, char R, char G, char B, double smoothv){
    vec2d lineVec = {  .x=x1-x0, .y=y1-y0 };
    vec2d nLineVec = { .x=x0-x1, .y=y0-y1 };
    vec2d normVec = { .x=-lineVec.y, .y=lineVec.x };
    normVec=normalize(normVec);
    for(int i = 0; i < HEIGHT; ++i){
        for(int j = 0; j < WIDTH; ++j){
            vec2d pointVec  = { .x=j-x0, .y=i-y0 };
            vec2d nPointVec = { .x=j-x1, .y=i-y1 };
            if(dotProduct(pointVec,lineVec)>=0 && dotProduct(nPointVec,nLineVec) >= 0){
                if(modulus(pointVec)==0.0f){
                    putPixel(dest,j,i,R,G,B);
                }else{
                    double pThickness = CLAMP(0,(thickness-fabs(modulus(projn(pointVec,normVec))))/smoothv,1);
                    putPixelAlpha(dest,j,i,R,G,B,pThickness);
                }
            }
        }
    }
}

double starLineTest(double x, double y, double theta, double scale, int n, double smoothv){
    double theta2=((int)(n/2)/(double)(n))*(2*M_PI);//works
    double x0=scale*sin(theta);
    double y0=scale*cos(theta);
    double x1=scale*sin(theta+theta2);
    double y1=scale*cos(theta+theta2);
    double a=y0-y1;
    double b=x1-x0;
    double c=x0*y1-y0*x1;
    double ret=0.0f;
    ret=CLAMP(0.0f,(a*x+b*y-c)/smoothv,1.0f);
    return ret;
}

void drawStarN(unsigned char * dest, int n, double rot, double x0, 
    double y0, double scale, char R, char G, char B, double smoothv){
    //drawCircle(dest,x0,y0,scale,R,G,B,smoothv);
    double theta=M_PI+rot;
    double x, y;
    for(int i = MAX(y0-scale*1.1f,0); i < MIN(y0+scale*1.1f,HEIGHT); ++i){
        for(int j = MAX(x0-scale*1.1f,0); j < MIN(x0+scale*1.1f,WIDTH); ++j){
            x=j-x0;
            y=i-y0;
            double alpha=1.0f;
            theta=M_PI+rot;
            int test_counter=0;
            double buf=0.0f;
            for(int i = 0; i < n; ++i,theta+=(2.0f*M_PI/n)){
                buf=starLineTest(x,y,theta,scale,n,smoothv);
                if(buf!=0.0f){
                    alpha=MIN(buf,alpha);
                    ++test_counter;
                }
            }
            //used for primitive anti-aliasing
            if(test_counter==(n/2)+2){
                putPixelAlpha(dest,j,i,R,G,B,alpha);
            }else if(test_counter>(n/2)+2){
                putPixel(dest,j,i,R,G,B);
            }

        }
    }
}
