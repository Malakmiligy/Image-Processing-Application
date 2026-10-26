#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;


void DarkenandLighten(Image& image) {
    int percentage;
    cout << "Enter percentage (0 to 100): ";
    cin >> percentage;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                int pix = image(i, j, k);

                if (percentage < 50)  
                    pix = pix * percentage / 50; //Darken //we want the original value to be 50 so we divide by 50 in case the percentage is 50 the output will be 1   
                    pix = pix + (255 - pix) * (percentage - 50) / 50; // lighten, same logic that we want the original value to be 50 
//note: bntr7 mn 255 3shan n2rb el value l 255 which is a3la value
                image(i, j, k) = pix;
            }
        }
    }
}
