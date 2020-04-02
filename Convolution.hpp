#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "Image.hpp"

enum class ApronStyle { ZERO, EXTEND, MIRROR, WRAP };

int convolve(int col, int row, Image &img);

Image::Rgb getImageValue(int col, int row, ApronStyle apron, const Image &img);

Image convolve(const Image &img, const Image &filter);

Image::Rgb convolve(int col, int row, const Image &img, const Image &filter);

#endif
