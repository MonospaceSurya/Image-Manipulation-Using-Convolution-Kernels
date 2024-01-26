#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


void main(){
    int w,h,c;
    unsigned char *img=stbi_load("grays.jpg",&w,&h,&c,0);
    stbi_write_png("Qatar.png",w,h,c,img,w*c);
    stbi_image_free(img);
}