#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


int convolve(int s1m,int s1n,int s2m,int s2n,uint8_t (*a)[s1m][s1n],int (*b)[s2m][s2n]){
    if(s1m!=s2m||s1n!=s2n){
        return 0;
    }
    int sum=0;
    int pop;
    for(int i=0;i<s1m;i++){
        for(int j=0;j<s1n;j++){
            pop=(int)(*a)[i][j]*(*b)[i][j];
            sum+=(pop);
            
        }
    }


    return sum;
}


int pix(unsigned char *img,int x,int y,int w,int h,int c){return x*c+y*w*c;}

int convolver(unsigned char *img,int w,int h,int c,int radius,int (*kern)[radius][radius]){


    int bg=(c==4)?4:3,imagebytes=w*h*bg;
    unsigned char *bimg =malloc(imagebytes),*p=img,*pg=bimg;
    int size=2*radius+1,k=1/(radius*radius);

    int total=(h)*(w),count=0;
    float prc=0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){

            count+=1;
            if(count%10000==0){
                prc=(count/(float)total)*100;
                printf("\n%.2f",prc);
            }

            if(i>=radius&&j>=radius&&i<h-radius&&j<w-radius){
            uint8_t imarr[size][size];
            uint8_t imarg[size][size];
            uint8_t imarb[size][size];

            int r1=0,c1=0;
            for(int t=-radius;t<=radius;t++){c1=0;
                for(int r=-radius;r<=radius;r++){
                    
                    imarr[r1][c1]=(uint8_t)*(p+pix(img,j+r,i+t,w,h,c));
                    imarg[r1][c1]=(uint8_t)*(p+pix(img,j+r,i+t,w,h,c)+1);
                    imarb[r1][c1]=(uint8_t)*(p+pix(img,j+r,i+t,w,h,c)+2);
                    
                    c1++;


                }
                r1++;
            }
            
            int (*kerne)[radius][radius]=kern;
            
            int f1=convolve(size,size,size,size,&imarr,kerne)/9;
            int f2=convolve(size,size,size,size,&imarg,kerne)/9;
            int f3=convolve(size,size,size,size,&imarb,kerne)/9;

            uint8_t t1=f1,t2=f2,t3=f3;
            int lo=pix(img,j,i,w,h,c);
            *(pg+lo)=t1;
            *(pg+lo+1)=t2;
            *(pg+lo+2)=t3;

            if(c==4){
                int k=pix(img,j,i,w,h,c);
                *(pg+lo+3)=*(p+k);
            }




            }
            else{
                int lo=pix(img,j,i,w,h,c);
                *(pg+lo)=*(p+pix(img,j,i,w,h,c));
                *(pg+lo+1)=*(p+pix(img,j,i,w,h,c)+1);
                *(pg+lo+2)=*(p+pix(img,j,i,w,h,c)+2);

                if(c==4){
                    *(pg+lo+3)=*(p+pix(img,j,i,w,h,c));
                }

            }





        }
    }
    printf("\n100.00");
    stbi_write_jpg("convolver.jpg",w,h,bg,bimg,100);
}

void main(){
    int w,h,c;
    unsigned char *img=stbi_load("island.jpg",&w,&h,&c,3);
    int radius=3;
    int kernel[3][3]={{1,1,1},{1,1,1},{1,1,1}};
    convolver(img,w,h,c,radius,&kernel);
}