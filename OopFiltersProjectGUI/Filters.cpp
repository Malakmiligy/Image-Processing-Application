//CS213 - Assignment 1 - Part 2

// Section S25

// Mariam Ahmed Kamal Eid   20250632   → Filters GrayScale(1), Flip (5),Merge (9), WanoBrightnessCorrection(13)
// Menna Omar Mohammad Mahmoud 20250676 → Filters Black And White (2), Rotate(6), Detect (10), Television (14)
// Malak Miligy Fathy Milig    20251422 → Filters Invert(3), Darken and Lighten(7), Crop (11), Purple (15)
// Nagham Mohasseb Ali Mohasseb   20251457 → Filters Frame(4), Resize(8), Blur (12), Infrared (16)

#include "Filters.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
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
void mframe (Image& image, int frametype, int r, int g, int b){

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
void Flip(Image& image, int choice)
{
    // watched a 5 min video on youtube for this: https://youtu.be/Yn_8KXuBXMc?si=DLgAEaFW_Pbn_0in

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
void RotateImage(Image& image, int rotationAngle)
{
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
void DarkenandLighten(Image& image, int percentage) {

    for (int i=0;i<image.width;i++) {
        for (int j=0;j<image.height; j++) {
            for (int k=0; k<3; k++) { //k is the pixel's color channel which are red green and blue
                unsigned int pix = image(i,j,k);

                if (percentage < 50) {

                    double factor = percentage/50.0;
                    image (i,j,k) = pix*factor; //Darkening because we multiply the RGB value by a value less than 1
                }
                else if (percentage > 50) {

                    double factor = (percentage - 50)/50.0;
                    unsigned int value = pix + (255-pix)*factor; //the new RGB value
                    if (value> 255) {
                        value = 255;
                    }
                    image (i,j,k) = value; //Lightening because we increase the RGB value and move it closer to 255
                }
            }
        }
    }
}

//Filter 8: Resize
void resize (Image& image, int newwidth, int newheight){

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
    }
    image = newimage;
}

// Filter 9: Merge
void Merge(Image& image1, Image& image2, int choice) {

    // Ensure both images have the same dimensions
    if(image1.width != image2.width || image1.height != image2.height) {

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
// x and y are the starting point, W and H are the width and height of the cropped area
bool CropImage(Image& image, int x, int y, int W, int H)
{
    if ( x<0 || y<0 || W<=0 || H<=0 || x+W>image.width || y+H>image.height )
    {
        return false; // the output pic can't be 0*0 dimensions and can't be larger than the original pic
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
    return true;
}

//Filter 12: Blur
void blur(Image& image, int radius){

    int width = image.width;
    int height = image.height;

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

//Filter 14: TV Filter
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

//Skewing filter
void skewing(Image& image, double degree){

    double angle;
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

//Oil Painting Filter

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
