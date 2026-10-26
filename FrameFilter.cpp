#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;

void mframe (Image& image){
int frametype ;
    int r , g , b;

cout<< "Choose frame type (1 = simple frame , 2 = decorated frame) ";
cin>>frametype;
cout << "inter frame color (r g b) (ex. 255 0 0):  ";
cin>> r >>g >>b;
    
    if(frametype==1){  
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j< image.height; j++){
            if((i<20) ||(i>= image.width - 20) ||(j<20) ||(j>=image.height - 20)){
                image(i,j,0)=r;
                image(i,j,1)=g;
                image(i,j,2)=b;
            }}}
        }


else if(frametype==2){
 for(int i = 0; i < image.width; i++){
        for(int j = 0; j< image.height; j++){
            if((i<20) ||(i>= image.width - 20) ||(j<20) ||(j>=image.height - 20)){
                image(i,j,0)=r;
                image(i,j,1)=g;
                image(i,j,2)=b;
            }
            if(((i>20) && (i<25))||((i >= image.width - 25)&&(i<= image.width -20 ))||((j>20)&&(j<25))||((j >= image.height - 25)&&(j<= image.height -20 ))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
            if(((i<20)&&(j<20))||((i<20)&&(j >= image.height -20))||((i>=image.width -20)&&(j<20))||((i>=image.width -20)&&(j >= image.height -20))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
            if(((i>26 && i<35)&&(j>26 && j<70))||(((j>26 && j<35)&&(i>26 && i<70))) ||((i<image.width -26 && i>image.width -35)&&(j<image.height-26 && j>image.height -70))||(((j<image.height -26 && j>image.height -35)&&(i<image.width -26 && i>image.width -70)))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
        }}
        }
}


