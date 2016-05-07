#include<math.h>
#include"main.h"

vec2d mkVec(double x, double y){
    vec2d retVec ={.x=x,.y=y};
    return retVec;
}

vec2d scalarMult(double a, vec2d t){
    return mkVec(t.x*a,t.y*a);
}

vec2d normalize(vec2d i){
    double mod=modulus(i);
    return mkVec(i.x*mod,i.y*mod);;
}

double modulus(vec2d i){
    return sqrt(i.x*i.x+i.y*i.y);
}

double dotProduct(vec2d a, vec2d b){
    return a.x*b.x+a.y*b.y;
}

vec2d projn(vec2d vec, vec2d base){
    return scalarMult(dotProduct(vec,base)/(modulus(base)*modulus(base)),base);
}
