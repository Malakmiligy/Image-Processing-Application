#pragma once
#include "Image_Class.h"

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
void PurpleFilter(Image& image);

//Nagham
void mframe(Image& image);
Image resize (Image image);
void infrared(Image& image);
Image blur(Image image);

//Bonus Filters
void oilpainting(Image& image);
Image skewing(Image image);


