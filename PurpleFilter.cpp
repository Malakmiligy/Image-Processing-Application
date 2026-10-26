#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;

void PurpleFilter (Image& image) //colot theory: red+blue=purple so we will increase red and blue values and decrease green
{
    for (int i=0; i<image.width; i++) {
        for (int j=0; j<image.height; j++)
        {
            image(i,j,0)=min(255, image(i,j,0)+ 20); //increase red
            image(i,j,1)= image(i,j,1)*0.75; //decrease green
            image (i,j,2)= min(255, image(i,j,2)+ 40); //increase blue //we use min beacuse RGB values can't exceed 255 so if the output valuse bigger than 255, it chooses 255 
        }
    }
}