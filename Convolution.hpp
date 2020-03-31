#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

enum class ApronStyle { ZERO, EXTEND, MIRROR, WRAP };

int convolve(int row, int col, Image &img);

double getImageValue(int col, int row, ApronStyle apron, Image img);

Image convolve(const Image &img, const Image &filter);

Rgb convolve(int row, int col, const Image &img, const Image &filter);

#endif
