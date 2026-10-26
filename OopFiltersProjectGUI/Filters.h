#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC

#include "Image_Class.h"

// ---- filters with no input ----
void GrayScaleConversion(Image& image);
void BlackAndWhiteFilter(Image& image);
void Invert(Image& image);
void ImageEdge(Image& image);
void WanoSunlightCorrection(Image& image);
void TvFilter(Image& image);
void PurpleFilter(Image& image);
void infrared(Image& image);
void oilpainting(Image& image);

// ---- filters that take parameters (no more cin/cout) ----
void mframe(Image& image, int frametype, int r, int g, int b); // frametype: 1 = simple, 2 = decorated
void Flip(Image& image, int choice);                           // 1 = vertical, 2 = horizontal
void RotateImage(Image& image, int rotationAngle);             // 90, 180, 270
void DarkenandLighten(Image& image, int percentage);           // 0..100
void resize(Image& image, int newwidth, int newheight);
void Merge(Image& image1, Image& image2, int choice);          // choice: 1 = resize then merge, 2 = common area
bool CropImage(Image& image, int x, int y, int W, int H);      // returns false if values are invalid
void blur(Image& image, int radius);
void skewing(Image& image, double degree);
