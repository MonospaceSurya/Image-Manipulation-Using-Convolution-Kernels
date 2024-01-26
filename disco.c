#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"




int pix(unsigned char *im,int x, int y,int w,int h, int c){
    unsigned char *p=im;

    int xpix=x*c,ypix=y*w*c,k;
    k=(xpix+ypix);

    return k;
}
int rgb(unsigned char *img,int *w,int *h,int *c,int r,int g,int b){
    
    //can younloop through a array using a pointer?
    //int rgbt=0;
    int image_size=(*w)*(*h)*(*c);
    int gb=(*c==4)?4:3;
    int bytes=*w**h*gb;
    unsigned char *rgbimg=malloc(bytes);

    unsigned char *p=img,*pg=rgbimg;
    printf("\nbox");

    


    for(int i=0;i<*h;i++){
        for(int j=0;j<*w;j++){
            int k=pix(img,j,i,*w,*h,*c);
            uint8_t l=0;
            if(k>1){
                *(pg)=(uint8_t)*(p+k+2);
            }
            else{
                *(pg)=*(p);
            }

            if(k<1){
                *(pg+1)=(uint8_t)*(p+k+1);
            }
            else{
                *(pg+1)=l;
            }

            if(g==1){
                *(pg+2)=(uint8_t)*(p+k);
            }
            else{
                *(pg+2)=l;
            }


            if(*c==4){
                *(pg+3)=*(p+k+3);
            }
            pg+=gb;
        }
    }


    

    stbi_write_jpg("rgb.jpg",*w,*h,gb,rgbimg,100);
    printf("\nbox2");
}


void main(){
    int w,h,c;
    unsigned char *img=stbi_load("road.jpg",&w,&h,&c,3);
    printf("\nImage Loaded Successfully");
    printf("\nWidth:%i\nHeight:%i\nChannels:%i",w,h,c);




    rgb(img,&w,&h,&c,1,1,1);
    stbi_image_free(img);
    printf("\n%i",pix(img,1,0,w,h,c));
}