#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

uint8_t mmult( int s1m, int s1n, int s2m, int s2n, uint8_t (*a)[s1m][s1n], uint8_t (*b)[s2m][s2n],uint8_t (*save)[s1m][s2n]){
    if(s1n!=s2m){
        return 0;
    }
    else{
        uint8_t sum;
        for(int i=0;i<s1m;i++){
            for(int l=0;l<s2n;l++){
                sum=0;
                for(int k=0;k<s2m;k++){
                    sum+=((*a)[i][k]*(*b)[k][l]);
                }
                (*save)[i][l]=sum;
            }
        }
    }
    //disp(save,s1m,s2n);

}

void disp(int m,int n, uint8_t (*array)[m][n]){
    printf("\n\n");
    for(int i=0;i<m;i++){printf("\n");
        for(int k=0;k<n;k++){
            printf(" %u ",(*array)[i][k]);
        }
    }
    printf("\n\n");
}

int convolve(int s1m,int s1n,int s2m,int s2n,uint8_t (*a)[s1m][s1n],int (*b)[s2m][s2n]){
    if(s1m!=s2m||s1n!=s2n){
        return 0;
    }
    int sum=0;
    int pop;
    for(int i=0;i<s1m;i++){
        for(int j=0;j<s1n;j++){
            pop=((int)(*a)[i][j])*(*b)[i][j];
            sum+=(pop);
        }
    }
    
    return sum;
}


void dispi(int m,int n, int (*array)[m][n]){
    printf("\n\n");
    for(int i=0;i<m;i++){printf("\n");
        for(int k=0;k<n;k++){
            printf(" %i ",(*array)[i][k]);
        }
    }
    printf("\n\n");
}
int pix(unsigned char *im,int x, int y, int w,int h,int c){return x*c+y*w*c;}

void boxblur(unsigned char *image,int w,int h,int c, unsigned char *save){

    int kernel[3][3]={{1,1,1},{1,1,1},{1,1,1}};

    dispi(3,3,&kernel);

    //SomethingRandom{{-1,-1,-1},{-1,8,-1},{-1,-1,-1}}
    //BowxBluwr{{1,1,1},{1,1,1},{1,1,1}}
    //Image Sharpenign{{0,-1,0},{-1,5,-1},{0,-1,0}}
    //GaussianItseems{{1,2,1},{2,4,2},{1,2,1}}
    //EMBOSSS{{-2,-1,0},{-1,1,1},{0,1,2}}
    //EdgeDetection{{0,1,0},{1,-4,1},{0,1,0}}
    //{{-1,0,1},{-2,0,2},{-1,0,1}}

    int image_size=w*h*c;
    int gb=(c==4)?4:3;
    int bytes=w*h*gb;
    unsigned char *bimg=malloc(bytes);

    unsigned char *p=image,*pg=bimg;





    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            
            

            if(i>=1&&j>=1&&i<h-1&&j<w-1){
                
                

                uint8_t imarr[3][3]={
                {*(p+pix(image,j-1,i-1,w,h,c)),*(p+pix(image,j,i-1,w,h,c)),*(p+pix(image,j+1,i-1,w,h,c))},
                {*(p+pix(image,j-1,i,w,h,c)),*(p+pix(image,j,i,w,h,c)),*(p+pix(image,j+1,i,w,h,c))},
                {*(p+pix(image,j-1,i+1,w,h,c)),*(p+pix(image,j,i+1,w,h,c)),*(p+pix(image,j+1,i+1,w,h,c))},
                };

                uint8_t imarg[3][3]={
                {*(p+pix(image,j-1,i-1,w,h,c)+1),*(p+pix(image,j,i-1,w,h,c)+1),*(p+pix(image,j+1,i-1,w,h,c)+1)},
                {*(p+pix(image,j-1,i,w,h,c)+1),*(p+pix(image,j,i,w,h,c)+1),*(p+pix(image,j+1,i,w,h,c)+1)},
                {*(p+pix(image,j-1,i+1,w,h,c)+1),*(p+pix(image,j,i+1,w,h,c)+1),*(p+pix(image,j+1,i+1,w,h,c)+1)},
                };

                uint8_t imarb[3][3]={
                {*(p+pix(image,j-1,i-1,w,h,c)+2),*(p+pix(image,j,i-1,w,h,c)+2),*(p+pix(image,j+1,i-1,w,h,c)+2)},
                {*(p+pix(image,j-1,i,w,h,c)+2),*(p+pix(image,j,i,w,h,c)+2),*(p+pix(image,j+1,i,w,h,c)+2)},
                {*(p+pix(image,j-1,i+1,w,h,c)+2),*(p+pix(image,j,i+1,w,h,c)+2),*(p+pix(image,j+1,i+1,w,h,c)+2)},
                };


            
            


            int ft1=(convolve(3,3,3,3,&imarr,&kernel)),ft2=(convolve(3,3,3,3,&imarg,&kernel)),ft3=(convolve(3,3,3,3,&imarb,&kernel));

            uint8_t f1=(ft1/9),f2=(ft2/9),f3=(ft3/9);

            int lo=pix(image,j,i,w,h,c);
            
            *(pg+lo)=f1;
            *(pg+lo+1)=f2;
            *(pg+lo+2)=f3;

            if(c==4){
                *(pg+lo+3)=*(p+lo+3);
            }
            

            }
   
        } 
        
        
    }
    stbi_write_png("boxblur.png",w,h,gb,bimg,w*gb);
    


}



void main(){
    int w,h,c;
    unsigned char *img=stbi_load("boats.jpg",&w,&h,&c,0);

    boxblur(img,w,h,c,img);

    stbi_image_free(img);
}