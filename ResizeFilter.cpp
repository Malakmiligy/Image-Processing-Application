#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;

Image resize (Image image){
    int choice;
    int newwidth , newheight;
cout<<"1- Enter dimensions (width & height)\n";
cout<<"2- Enter ratio of reduction or increase\n";
cout<<"choose 1 or 2 ";
cin>> choice;

if(choice == 1){
    cout<<"Enter the dimensions (ex.1920  1080):   ";
    cin>> newwidth >> newheight;
}
else {
    double ratio;
    cout<<"Enter the ratio (ex. 0.2):  ";
    cin>> ratio;
    newwidth = image.width * ratio;
    newheight = image.height * ratio;
}

    Image newimage(newwidth,newheight);

double scaleX=(double)image.width / newwidth ;
double scaleY=(double)image.height / newheight;

for(int x=0; x < newwidth; x++){
    for(int y=0; y < newheight; y++){
       int sx = x * scaleX;
       int sy = y * scaleY;
        
       newimage(x,y,0)= image(sx,sy,0);
        newimage(x,y,1)= image(sx,sy,1);
        newimage(x,y,2)= image(sx,sy,2);
    }
} return newimage;
}

