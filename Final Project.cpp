//Final Project

// Mariam Ahmed  → Filters GrayScale(1), Flip (5),Merge (9), WanoBrightnessCorrection(13)
// Menna Omar  → Filters Black And White (2), Rotate(6), Detect (10), Television (14), GUI
// Malak Miligy → Filters Invert(3), Darken and Lighten(7), Crop (11), Purple (15), Oil Painting (18)
// Nagham Mohasseb  → Filters Frame(4), Resize(8), Blur (12), Infrared (16), Skewing (17)

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC

#include <iostream>
#include <string>
#include <cstring>
#include "Image_Class.h"
using namespace std;

//Mariam
void GrayScaleConversion(Image& image);
void WanoSunlightCorrection(Image& image);
void Flip(Image& image);
void Merge(Image& image);

//Menna
void BlackAndWhiteFilter(Image& image);
void RotateImage(Image& image);
void ImageEdge(Image& image);
void TvFilter(Image& image);

//Malak
void Invert(Image& image);
void DarkenandLighten(Image& image);
void CropImage (Image& image);
void PurpleFilter (Image& image);

//Nagham
void mframe(Image& image);
void resize (Image& image);
void infrared(Image& image);
void blur(Image& image);

//Bonus Filters
void oilpainting(Image& image);
void skewing(Image& image);

//function of saving the image after applying the filter 

void SaveImage(Image& image) {
    string outputFilename;
    cout << "Enter output filename (with extension): "; 
    cin >> outputFilename;
    image.saveImage(outputFilename);
}

int main() {

    //taking the name of the image
    string imageName;
    cout << "Please Enter Image name: ";
    cin >> imageName;
    Image image(imageName);

    //main menu logic (choosing the filter + exiting the app + saving the image USE THE SAVE IMAGE FUNCTION)


    int choice = -1;
    while(choice != 0)
    {
        cout <<  "_________Menu__________\n"
        << "1) GrayScale\n"
        << "2) Black and White\n"
        << "3) Invert\n"
        << "4) Frame\n"
        << "5) Flip Image\n"
        << "6) Rotate Image\n"
        << "7) Darken and Lighten\n"
        << "8) Resize\n"
        << "9) Merge Images\n"
        << "10) Image Edge\n"
        << "11) Crop \n"
        << "12) blur filter\n"
        << "13) brightness correction\n"
        << "14) Tv Filter\n"
		<< "15) Purple Effect\n"
		<< "16) infrared filter\n"
		<< "17) skewing filter\n"
        << "18) Oil Painting \n"
        << "19) Save Image\n"
        << "20) Load New Image\n"
        << "0) Exit\n"
        << "Choice:  ";

        cin >> choice;
        
        switch(choice)
    {
        case 1: GrayScaleConversion(image);  break;
        case 2: BlackAndWhiteFilter(image); break;
        case 3: Invert(image); break;
        case 4: mframe(image); break;
        case 5: Flip(image); break;
        case 6: RotateImage(image); break;
        case 7: DarkenandLighten(image); break;
        case 8: resize(image); break;
        case 9: Merge(image); break;
        case 10: ImageEdge(image); break;
        case 11: CropImage(image); break;
        case 12: blur(image); break;
		case 13: WanoSunlightCorrection(image); break;
		case 14: TvFilter(image); break;
		case 15: PurpleFilter(image); break;
		case 16: infrared(image); break;
		case 17: skewing(image); break;
        case 18: oilpainting(image); break;
        case 19: SaveImage(image); break;
        case 20:
        {
            cout << "Enter Image Name:  ";
            cin >> imageName;
            image = Image(imageName);
            break;
        };
        case 0:
        {
            char ans;
            cout << "Do you want to save your image? y/n";
            cin >> ans;
            if(ans == 'y' || ans == 'Y' ){SaveImage(image);}
            break; 

        }
        default: cout << "Invalid Choice.\n";


    }
        
    }
    
    return 0;
    
}

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

//Filter 2: Black and White 
void BlackAndWhiteFilter(Image& image)
{

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int avg = 0;

            for (int k = 0; k < image.channels; k++)
            {
                avg += image(i, j, k);
            }

            avg = avg / 3;

			if (avg > 127) //if closer to white turn white else turn black
            {
                for (int k = 0; k < image.channels; k++)
                {
                    image(i, j, k) = 255;
                }
            }
            else
            {
                for (int k = 0; k < image.channels; k++)
                {
                    image(i, j, k) = 0;
                }
            }

        }
    }
    
}

//Filter 3: Invert
void Invert(Image& image) {

 
    for (int i=0; i<image.width; i++)  
    {  
        for (int j=0; j<image.height; j++) { //invert every pixel's Red Green Blue Values 
        image(i,j,0)=255-image(i,j,0);  
        image(i,j,1)=255-image(i,j,1);  
        image(i,j,2)=255-image(i,j,2); }  
  
    }  
}
// Filter 4: Frame
void mframe (Image& image){
int frametype ;
    int r , g , b;

cout<< "Choose frame type (1 = simple frame , 2 = decorated frame) ";
cin>>frametype;
cout << "inter frame color (r g b) (ex. 255 0 0):  ";
cin>> r >>g >>b;
    
    if(frametype==1){  
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j< image.height; j++){
            if((i<20) ||(i>= image.width - 20) ||(j<20) ||(j>=image.height - 20)){
                image(i,j,0)=r;
                image(i,j,1)=g;
                image(i,j,2)=b;
            }}}
        }


else if(frametype==2){
 for(int i = 0; i < image.width; i++){
        for(int j = 0; j< image.height; j++){
            if((i<20) ||(i>= image.width - 20) ||(j<20) ||(j>=image.height - 20)){
                image(i,j,0)=r;
                image(i,j,1)=g;
                image(i,j,2)=b;
            }
            if(((i>20) && (i<25))||((i >= image.width - 25)&&(i<= image.width -20 ))||((j>20)&&(j<25))||((j >= image.height - 25)&&(j<= image.height -20 ))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
            if(((i<20)&&(j<20))||((i<20)&&(j >= image.height -20))||((i>=image.width -20)&&(j<20))||((i>=image.width -20)&&(j >= image.height -20))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
            if(((i>26 && i<35)&&(j>26 && j<70))||(((j>26 && j<35)&&(i>26 && i<70))) ||((i<image.width -26 && i>image.width -35)&&(j<image.height-26 && j>image.height -70))||(((j<image.height -26 && j>image.height -35)&&(i<image.width -26 && i>image.width -70)))){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;
            }
        }}
        }
}

//Filter 5: Flip
void Flip(Image& image)
{

    // watched a 5 min video on youtube for this: https://youtu.be/Yn_8KXuBXMc?si=DLgAEaFW_Pbn_0in

    int choice = 0;
    

    while(choice != 1 && choice != 2)
    {
    cout<<"1- Flip Vertically\n";
    cout<<"2- Flip Horizontally\n";
    cout<<"choose 1 or 2 ";
    cin>> choice;

     if(choice != 1 && choice != 2)
    {
        cout << "invalid Input, please try again";

    }
    }

    if(choice == 1)
    {
        for (int i = 0; i < image.width; i++)
    {
        unsigned char tmp[4]; //should be unsigned char because: bec pixels range from 0 to 255/ also it is 4 considering alpha so it will be not overflowed at tmp[3]
        int px1; 
        int px2;
        for (int j = 0; j < image.height/2; j++)
        {
           px1 = (i + j * image.width) * image.channels;
           px2 = (i + (image.height - 1 - j ) * image.width) * image.channels;

           memcpy(tmp, &image.imageData[px1], image.channels);
           memcpy(&image.imageData[px1], &image.imageData[px2], image.channels);
           memcpy(&image.imageData[px2], tmp, image.channels);

        }
    }
    
    }
    else if(choice == 2)
    {
for (int j = 0; j < image.height; j++)
    {
        unsigned char tmp[4]; //should be unsigned char because: also it is 4 considering alpha so it will be not overflowed at tmp[3]
        int px1; 
        int px2;
        for (int i = 0; i < image.width/2; i++)
        {
           px1 = (i + j * image.width) * image.channels;
           px2 = ((image.width - 1 - i) + j * image.width) * image.channels;

           memcpy(tmp, &image.imageData[px1], image.channels);
           memcpy(&image.imageData[px1], &image.imageData[px2], image.channels);
           memcpy(&image.imageData[px2], tmp, image.channels);

        }
    }
    }


    

}

//Filter 6: Rotate
void RotateImage(Image& image)
{

    

    int rotationAngle;
    cout << "Please enter the rotation angle (ex. 90, 180, 270)";
    cin >> rotationAngle;


    if (rotationAngle == 90)
    {
        Image rotatedImage(image.height, image.width);
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                rotatedImage(image.height - 1 - j , i, 0) = image(i, j, 0);
                rotatedImage(image.height - 1 - j , i, 1) = image(i, j, 1);
                rotatedImage(image.height - 1 - j , i , 2) = image(i, j, 2);
                
            }
        }
        image = rotatedImage;
    }
    else if (rotationAngle == 180)
    {
        Image rotatedImage(image.width, image.height);
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                rotatedImage(image.width - 1 - i, image.height - 1 - j, 0) = image(i, j, 0);
                rotatedImage(image.width - 1 - i, image.height - 1 - j , 1) = image(i, j, 1);
                rotatedImage(image.width - 1 - i, image.height - 1 - j , 2) = image(i, j, 2);

            }
        }
        image = rotatedImage;
    }
    else if (rotationAngle == 270)
    {
        Image rotatedImage(image.height, image.width);

        for (int i = 0; i < image.width; i++)
        {
            
            for (int j = 0; j < image.height; j++)
            {
                rotatedImage(j,image.width - 1 - i, 0) = image(i, j, 0);
                rotatedImage(j, image.width - 1 - i , 1) = image(i, j, 1);
                rotatedImage(j, image.width - 1 - i, 2) = image(i, j, 2);

            }
        }
        image = rotatedImage; 
    }
    

}

//Filter 7: Darken and Lighten
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

//Filter 8: Resize
void resize (Image& image){
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
} image = newimage;
}

//Filter 9: Merge
void Merge(Image& image1) {

    string image2Name;
     cout<<"Enter Image you want to merge: ";
     cin>> image2Name;

     Image image2;
     image2.loadNewImage(image2Name);
     int choice;

    // Ensure both images have the same dimensions
    if(image1.width != image2.width || image1.height != image2.height) {

     cout<<"1: Resize then merge\n";
     cout<<"2: Merge common area\n";
     cout<<"Choose an option: \n";
     cin>> choice;

     while(choice != 1 && choice != 2)
     {
        cout << "Invalid choice, Please choose 1 or 2: ";
        cin >> choice;
     }

     if(choice == 1) {
        int maxwidth = max(image1.width, image2.width);
        int maxheight = max(image1.height, image2.height);
        // as we will be resizing both images to max width and max height not just one 
        Image* imgs[2] = {&image1, &image2}; //as it is holding reference not copies (so I must add the &)

        for(int n = 0; n < 2; ++n) {
            Image* current = imgs[n];
            Image resized(maxwidth, maxheight);

            double scaleX=(double)current -> width / maxwidth ;
            double scaleY=(double)current -> height / maxheight;

            for(int x=0; x < maxwidth; x++){
                for(int y = 0; y < maxheight; y++){
                    int sx = x * scaleX;
                    int sy = y * scaleY;
                    resized(x,y,0)= (*current)(sx,sy,0);
                    resized(x,y,1)= (*current)(sx,sy,1);
                    resized(x,y,2)= (*current)(sx,sy,2);
                }
            }
            *current = resized;
        }
                    }

     else if (choice == 2) {
        //get min width and height to merge common area
        int minwidth = min(image1.width, image2.width);
        int minheight = min(image1.height, image2.height);
        Image common1(minwidth, minheight);
        Image common2(minwidth, minheight);

        for(int i = 0; i < minwidth; ++i) {
            for(int j =0; j < minheight; ++j) {
                for(int k = 0; k < 3; ++k) { // k < 3 because Image(w,h) creates 3 channel images (alpha is dropped here)
                    common1(i,j,k) = image1(i,j,k);
                    common2(i,j,k) = image2(i,j,k);
                }
            }
        }

        image1 = common1;
        image2 = common2;

     } 
    }

        // sometimes images like png can have an extra channel so they have 4 channels RGBA not just RGB 
        // so we shall do a check to avoid any overflow 
        int channels = min(image1.channels, image2.channels);
        
        // I could've directly replaced image1.channels to 3, but this would've led to distortion of colors or offsetting the image when it has more than 3 channels (like png images) so I used the min function to avoid that

        for(int i = 0; i < image1.width; ++i) {
            for(int j = 0; j < image1.height; ++j) {
                //I will not just iterate through each pixel, I need to iterate at each pixel's colour as well 
                for(int k = 0; k < channels; ++k) {
                    // then I will just average the pixels rpg values to give the merge effect (50 50 merge effect) 
                    //updating pixel data in image 1 (adding image 2 to image 1)
                    image1(i,j,k) = (image1(i,j,k) + image2(i,j,k))/2;
                }
                }

            }
        }

//Filter 10: Image Edge
void ImageEdge(Image& image)
{
    GrayScaleConversion(image);  //converting to gray scale essencially made all channels the same value so I can just work on 0

    Image original = image; 

     for (int i = 1; i < image.width - 1; i++)
    {
        for (int j = 1; j < image.height - 1; j++)
        {
           
            int horizontal = original( i+1 , j, 0) - original(i-1, j, 0);
            int Vertical = original(i, j+1, 0) - original(i, j-1, 0);

             int edgeStrength = abs(horizontal) + abs(Vertical);

         
               if(edgeStrength > 40)
                {
                    image(i,j,0) = 0;
                    image(i,j,1) = 0;
                    image(i,j,2) = 0;
                }
                else
                {
                    image(i,j,0) = 255;
                    image(i,j,1) = 255;
                    image(i,j,2) = 255;

                }
            
        }
    }

}

//Filter 11: Crop
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

// Filter 12: Blur

void blur(Image& image){
 
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
 image = blurred;
}

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

//Filter 14: TV
void TvFilter(Image& image)
{
    for(int i = 0; i < image.width; i++)
    {
         for (int j = 1; j < image.height; j++)
         {
            for (int k = 0; k < image.channels; k++)
            {
                if(j%2 == 1)
                {
                    image(i, j, k) = image(i, j, k)*0.7; 
                }
            }
         }
    }
}

//Filter 15: Purple
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

//Filter 16: Infrared

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


//Filter 17: Skewing

void skewing(Image& image){
   
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
image = newimage;
}

//Filter 18: Oil Painting 

// logic of the code :
//Uses a radius of 4 pixels around each pixel, creating a 9x9 square
// Groups the pixels in this square into 20 levels based on intensity
// Finds the level that contains the most pixels
// Calculates the average RGB color of the pixels in that level
// Uses this color for the current pixel so it looks like oil painting

void oilpainting(Image& image)
{
    int radius = 4; // This is the size of the pixel block around each centered pixel
    int levels = 20; // Divides the 256 intensity values into 20 levels to group colors

    Image result(image.width, image.height); // Creates a new image to store the result 3shan my7slsh conflicts

    for (int i=0; i< image.width; i++)
    {
        for (int j=0; j<image.height; j++)
        {
            // Counts pixels and stores the sum of their RGB values for each intensity level
            int count[20]={0};
            int red[20]={0};
            int green[20]={0};
            int blue[20]={0};

            // ncheck kol el pixels elly fe el radius
            for (int x= -radius; x<= radius; x++)
            {
                for (int y= -radius; y<= radius; y++)
                {
                    int px = i+x; // Calculates the x-coordinate of the nearby pixel
                    int py = j+y; // Calculates the y-coordinate of the nearby pixel

                    // Checks en el pixel gowa el image boundaries
                    if (px >= 0 && px < image.width && py >= 0 && py < image.height)
                    {
                        // Gets the red, green, and blue values of the pixel
                        int r = image(px,py,0);
                        int g = image(px,py,1);
                        int b = image(px,py,2);
                        
                        int intensity = (r + g + b) / 3;

                        // Assigns the pixel to the level it belongs to 
                        int level = intensity * levels / 256;

                        // Counts pixels in this level and adds their RGB values 3shan hana5od el level elly feh akbar 3dd pixels
                        count[level]++;
                        red[level] += r;
                        green[level] += g;
                        blue[level] += b;
                    }
                }
            }
            int maxLevel =0; // Stores the level containing the most pixels

            // Finds the intensity level with the highest pixel count
            for (int k=1; k < levels; k++)
            {
                if (count[k] > count[maxLevel])
                {
                    maxLevel=k;
                }
            }
            result(i, j, 0) = red[maxLevel] / count[maxLevel];
            result(i, j, 1) = green[maxLevel] / count[maxLevel];
            result(i, j, 2) = blue[maxLevel] / count[maxLevel];
        }
    }

    image = result; // Replaces the original b el edited image 
}
