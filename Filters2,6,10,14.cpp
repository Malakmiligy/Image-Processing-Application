#define _CRT_SECURE_NO_WARNINGS  //Because my script is freaking out about some functions in the Image library apparently so I'm telling it it's safe

#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"

using namespace std;

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

void ImageEdge(Image& image)
{
    bool IsEdge;
     for (int i = 1; i < image.width - 1; i++)
    {
        for (int j = 1; j < image.height - 1; j++)
        {
            for (int k = 0; k < image.channels; k++)
            {
                int horizontal = image(i+1, j, k) - image(i-1, j, k);
                int Vertical = image(i, j+1, k) - image(i, j-1, k);

                int edgeStrength = abs(horizontal) + abs(Vertical);


                if(edgeStrength > 100)
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

}
void ImageEdge(Image& image)
{
    //GrayScaleConversion(image); (in a diffrent script) //converting to gray scale essencially made all channels the same value so I can just work on 0

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

