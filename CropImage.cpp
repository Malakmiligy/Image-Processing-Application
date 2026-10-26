#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
using namespace std;  
  
void CropImage(Image& image)
{
    unsigned int x,y,W,H; 
    // All values must be positive 
    //x and y are the starting point where the user wants to crop, W and H are the width and height of the cropped area
    cout << "Image dimensions: " << image.width << " x " << image.height << endl; //i wanted to add a feature that let the user know the dimmensions before using the filter
    cout<< "Enter Starting points: x, y and Dimensions: W and H";
    cin >>x>>y>>W>>H;
    if ( W==0 || H==0 || x+W>image.width || y+H>image.height )
    {
        cout << "Invalid Values" << endl; // the output pic can't be 0*0 dimensions and can't be larger than the original pic
        return;
    }

    Image cropped (W,H);
    for (int i=0; i<W; i++)
    {
        for (int j=0; j<H; j++)
        {
            for (int k=0; k<3; k++) //to scan all pixels and their RGB channels
            {
                cropped (i,j,k)=image(x+i, y+j, k);  //copy pixels from the the selected area of the original image
        }
        }
        }
        image = cropped;
}