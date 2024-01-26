#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void disp(int m,int n, int (*array)[m][n]){
    printf("\n\n");
    for(int i=0;i<m;i++){printf("\n");
        for(int k=0;k<n;k++){
            printf(" %i ",(*array)[i][k]);
        }
    }
    printf("\n\n");
}

int grayscale(unsigned char *img,int *w,int *h,int *c, unsigned char *img_out,int save_or_update){

    int image_size=(*w)*(*h)*(*c);
    int gray_channels=(*c==4)?2:1;
    unsigned char *gray_image=malloc((*w)*(*h)*(gray_channels));

    for(unsigned char *p=img, *pg=gray_image;p!=img+image_size;p+=*c,pg+=gray_channels){
        *pg=(uint8_t)(*(p)*0.299+*(p+1)*0.587+*(p+2)*0.114);
        if(gray_channels==2){
            *(pg+1)=*(p+3);
        }
    }
    if(save_or_update==1){
        stbi_write_jpg("grays.jpg",*w,*h,gray_channels,gray_image,100);
    }
    else{
        *img_out=*gray_image;
    }
    



}
void main(){
    int w,h,c;
    unsigned char *img=stbi_load("Qatar.png",&w,&h,&c,0);

    grayscale(img,&w,&h,&c,img,1);
    stbi_image_free(img);
}