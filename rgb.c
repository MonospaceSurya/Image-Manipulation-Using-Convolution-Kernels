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
            if(r==1){
                *(pg)=(uint8_t)*(p+k+1);
            }
            else{
                *(pg)=*(p);
            }

            if(g==1){
                *(pg+1)=(uint8_t)*(p+k);
            }
            else{
                *(pg+1)=l;
            }

            if(b==1){
                *(pg+2)=(uint8_t)*(p+k+2);
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
    unsigned char *img=stbi_load("Qatar.jpg",&w,&h,&c,3);
    printf("\nImage Loaded Successfully");
    printf("\nWidth:%i\nHeight:%i\nChannels:%i",w,h,c);
 /*   bw(img,&w,&h,&c,img,1);
    stbi_image_free(img);


    int a[3][3]={{1,2,3},{3,4,5},{5,6,7}},b[3][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0}},ans[3][4];
    int (*p)[3][3]=&a,(*p1)[3][4]=&b,(*pans)[3][4]=&ans;
    disp(3,3,&a);
    disp(3,4,&b);
    mmult(3,3,3,4,&a,&b,&ans);
    disp(3,4,&ans);
*/



    rgb(img,&w,&h,&c,1,1,1);
    stbi_image_free(img);
    printf("\n%i",pix(img,1,0,w,h,c));
}






/*
int gray(unsigned char *img,int *w,int *h,int *c){

    //can younloop through a array using a pointer?
    int rgbt=0;
    int image_size=(*w)*(*h)*(*c);

    unsigned char *p=img,image_matrix[*w][*h][*c], (*imp)[*w][*h][*c]=&image_matrix; 
    int gb=(*c==4)?2:1;
    int bytes=*w**h*gb;
    unsigned char *grayscaleimg=malloc(bytes), *pg=grayscaleimg;
    for(int i=0;i<*h;i++){
        for(int j=0;j<*w;j++,rgbt++,p+=*c){
            image_matrix[j][i][rgbt]=(*p);
            image_matrix[j][i][rgbt+1]=(*p+1);
            image_matrix[j][i][rgbt+2]=(*p+2);
            if(*c==4){
                image_matrix[j][i][rgbt+3]=(*p+3);
            }
        }
    }

    rgbt=0;
    for(int i=0;i<*h;i++){
        for(int j=0;j<*w;j++){
        *pg=(uint8_t)((*imp)[j][i][rgbt]*0.299+(*imp)[j][i][rgbt+1]*0.587+(*imp)[j][i][rgbt+2]*0.114);
        if(*c==4){
            *(pg+1)=(*imp)[j][i][rgbt+3];
        }
        pg+=gb;       
        }
    }
    stbi_write_jpg("boxxblur.jpg",*w,*h,gb,grayscaleimg,100);
}


*/