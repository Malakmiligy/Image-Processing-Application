# include "Image_Class.h"

void infrared(Image& image){
    for(int i=0;i<image.width;i++){
        for(int j =0; j< image.height;j++){
            unsigned int r = image(i,j,0);
            unsigned int g = image (i,j,1);
            unsigned int b = image(i,j,2);
         
            //Calculate brightness using luminance formula to consider different eye senstivities to colors
            unsigned int brightness=((0.299 *r) + (0.587 *g) +(0.114*b));

            image(i,j,0)=255;
            //Multiply by 0.7 to reduce color intensity and balance the tones
            image(i,j,1)=(255-brightness)*0.7;
            image(i,j,2)=(225-brightness) *0.7;
                
            }
        }
    }

