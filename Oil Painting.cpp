#include "Image_Class.h"

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