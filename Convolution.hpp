#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "Image.hpp"

enum class ApronStyle { ZERO, EXTEND, MIRROR, WRAP };

int convolve(int row, int col, Image &img);

Image::Rgb getImageValue(int col, int row, ApronStyle apron, const Image &img);

Image convolve(const Image &img, const Image &filter);

Image::Rgb convolve(int row, int col, const Image &img, const Image &filter);

#endif
