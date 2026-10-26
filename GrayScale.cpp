#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;

//Filter 1: Grayscale Conversion

void GrayScaleConversion(Image& image)
{

        for(int i = 0; i < image.width; ++i){
        for(int j = 0; j < image.height; ++j){
            //so it is never -ve
            unsigned int avg = 0;

            for(int k = 0; k < image.channels; ++k){
                //to presrve the details of the image
                avg += image(i,j,k);
            }

        avg = avg/3;
        // making them gray but et you can see the details of the image
        for(int k = 0; k< image.channels; ++k){
            image(i,j,k) = avg;
        }
        }
    }

}
