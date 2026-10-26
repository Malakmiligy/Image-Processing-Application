#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;

//Filter 13: Wano sunlight correction


void WanoSunlightCorrection(Image& image)
{

        for(int i = 0; i < image.width; ++i){
        for(int j = 0; j < image.height; ++j){
           int r = image(i,j,0);
           int g = image(i,j,1);
           int b = image(i,j,2);
           //checking brightness (but the better way was to check it on how it is being actually preserved by human eyes)
           int brightness = (r + g + b) / 3;

           //if it was bright 
           if(brightness > 128)
           {
            r = r + 25;
            g = g + 15;
            b = b -5;

           }
           //if it was dark 
           else
           {
            r = r - 15;
            g = g - 15;
            b = b + 10;
           }

           //I need to make sure the values don't go over 255 or lower than 0

           if(r>255) r = 255;
           if(g>255) g = 255;
           if(b>255) b = 255;

           if(r<0) r = 0;
           if(g<0) g = 0;
           if(b<0) b = 0;

           image(i,j,0) = r;
           image(i,j,1) = g;
           image(i,j,2) = b;

        }
    }
}

