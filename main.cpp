//CS213 - Assignment 1 - Part 1

// Section S25

// Mariam Ahmed Kamal Eid   20250632   → Filters GrayScale(1), WanoBrightnessCorrection(13).
// Menna Omar Mohammad Mahmoud 20250676 → Filters Black And White (2), Rotate(6)
// Malak Miligy Fathy Milig    20251422 → Filters Invert(3), Darken and Lighten(7), Crop Image (11), Purple Filter (15)
// Nagham Mohasseb Ali Mohasseb   20251457 → Filters Frame(4), Resize(8)


//File: CS213_A1_Part1_S25_20250632_20250676_20251422_20251457.cpp

#include <iostream>
#include <string>
#include "Filters.h"
using namespace std;

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
        << "5) Rotate Image\n"
        << "6) Darken and Lighten\n"
        << "7) Resize\n"
        << "8) brightness correction\n"
        << "9) Crop \n"
        << "10) Purple Effect\n"
        << "11) Oil Painting \n"
        << "12) Flip Image\n"
        << "13) Image Edge\n"
        << "14) Tv Filter\n"
		<< "15) blur filter\n"
		<< "16) infrared filter\n"
		<< "17) skewing filter\n"
        << "18) Merge Images\n"
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
        case 5: RotateImage(image); break;
        case 6: DarkenandLighten(image); break;
        case 7: image= resize(image); break;
        case 8: WanoSunlightCorrection(image); break;
        case 9: CropImage(image); break;
        case 10: PurpleFilter(image); break;
        case 11: oilpainting(image); break;
        case 12: Flip(image); break;
        case 13: ImageEdge(image); break;
        case 14: TvFilter(image); break;
		case 15: image= blur(image); break;
		case 16: infrared(image); break;
		case 17: image= skewing(image); break;
        case 18: Merge(image); break;
        case 19: SaveImage(image); break;
        case 20:
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
