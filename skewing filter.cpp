#include <iostream>
# include <cmath>
using namespace std;
# include "Image_Class.h"

Image skewing(Image image){
   
    double angle;
    double degree;
   // Read the skew degree from the user
   cout<<"Enter the degree of skewness\n";
    cin>> degree;
    // Convert degrees to radians 
    angle = degree *(M_PI / 180.0);
    // Horizontal shift per row = tan(angle) 
    double shiftfactor= tan(angle);
    // New width = old width + total horizontal shift 
    int newwidth = image.width + abs((int) (image.height * shiftfactor));
    int height = image.height;
  
   // Create the new (wider) image, same height
   Image newimage(newwidth , height);
  // maxshift = total shift at the bottom row
   int maxshift = abs((int)(image.height * shiftfactor));
   
   // For negative angles (skew to the left), push the image right by maxshift
    // so its left side doesn't get cut off. Otherwise no offset is needed.
   int startoffset = (shiftfactor<0) ? maxshift :0;
   
   for(int i = 0; i < newwidth ;i++){
    for(int j =0; j < height ;j++){
           
            int z= (int) (j * shiftfactor);
            // Find the matching pixel in the original image
            int oldi= i - z - startoffset ;
            int oldj = j;
        // If the source pixel is inside the original image, copy all 3 channels (RGB)
        if(oldi>=0 && oldi<image.width && oldj>=0 && oldj<image.height ){
        
        newimage(i,j,0)=image(oldi,oldj,0);
        newimage(i,j,1)=image(oldi,oldj,1);
        newimage(i,j,2)=image(oldi,oldj,2);
        }else{
           // Outside the original image: fill with white 
            newimage(i,j,0)=255;
            newimage(i,j,1)=255;
            newimage(i,j,2)=255;
        }
        
    }
   }
return newimage;
}
