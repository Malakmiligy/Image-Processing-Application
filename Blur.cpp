#include <iostream>
using namespace std;
# include "Image_Class.h"

Image blur(Image image){
 
 int width = image.width;
 int height = image.height;  
 int radius;
 
 cout<<"Enter the blurlevel :(1 or 2 or 3 ...etc)\n" ;
 cin>>radius;
   
 Image blurred(width , height);
   
 for (int i =0;i < image.height;i++){
     for (int j =0; j< image.width; j++){
       
         int counter=0; //Counts valid neighbor pixels 
        unsigned int sumr=0;
        unsigned int sumg=0;
        unsigned int sumb=0;
        
         for(int x=-radius; x<=radius;x++){
             for(int y=-radius;y<=radius;y++){
                
                //Skip out of bounds neighbor
                if(i+x >=0 && i+x < image.height && j+y >=0 && j+y < image.width ){
                    sumr += image(j+y, i+x ,0);
                    sumg += image(j+y,i+x ,1);
                    sumb += image(j+y, i+x ,2);
                    counter++;
                }
                
                }
             }
                 blurred(j,i,0)= sumr/counter;
                 blurred(j,i,1)= sumg/counter;
                 blurred(j,i,2)= sumb/counter;
         }
 }
 return blurred;
}