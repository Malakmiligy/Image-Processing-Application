//Filter 3: Invert
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;  
  
void Invert(Image& image) {

 
    for (int i=0; i<image.width; i++)  
    {  
        for (int j=0; j<image.height; j++) { //invert every pixel's Red Green Blue Values 
        image(i,j,0)=255-image(i,j,0);  
        image(i,j,1)=255-image(i,j,1);  
        image(i,j,2)=255-image(i,j,2); }  
  
    }  
}
