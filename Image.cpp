#include "Image.hpp"

Image::Rgb::Rgb() : r(0), g(0), b(0) {} 

Image::Rgb::Rgb(float c) : r(c), g(c), b(c) {} 

Image::Rgb::Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

bool Image::Rgb::operator!=(const Image::Rgb &c) const 
{ 
    return c.r != this->r || c.g != this->g || c.b != this->b;
} 
Image::Rgb& Image::Rgb::operator*=(const Image::Rgb &rgb) 
{ 
    this->r *= rgb.r, this->g *= rgb.g, this->b *= rgb.b; 
    return *this; 
} 
Image::Rgb& Image::Rgb::operator+=(const Image::Rgb &rgb) 
{ 
    r += rgb.r, g += rgb.g, b += rgb.b; 
    return *this; 
} 

float& operator+=(float &f, const Image::Rgb rgb) 
{ 
    f += (rgb.r + rgb.g + rgb.b) / 3.f; 
    return f; 
} 

Image::Image() : w(0), h(0), pixels(nullptr) { /* empty image */ } 

Image::Image(const Image &img, const Image::Rgb &c) : w(img.w), h(img.h), pixels(img.pixels) 
{ 
    for (int i = 0; i < w * h; ++i)
    {
        pixels[i] += c;
    }
} 

Image::Image(const unsigned int &_w, const unsigned int &_h, const Image::Rgb &c) : w(_w), h(_h), pixels(NULL) 
{ 
    pixels = new Rgb[w * h]; 
    for (int i = 0; i < w * h; ++i) 
        pixels[i] = c; 
}

const Image::Rgb& Image::operator[](const unsigned int &i) const 
{ 
    return pixels[i]; 
} 

Image::Rgb& Image::operator[](const unsigned int &i) 
{ 
    return pixels[i]; 
}

Image::~Image() 
{ 
    if (pixels != NULL) delete [] pixels; 
} 

const Image::Rgb Image::kBlack = Image::Rgb(0); 
const Image::Rgb Image::kWhite = Image::Rgb(1); 
const Image::Rgb Image::kRed = Image::Rgb(1,0,0); 
const Image::Rgb Image::kGreen = Image::Rgb(0,1,0); 
const Image::Rgb Image::kBlue = Image::Rgb(0,0,1);

Image readPPM(const char *filename) 
{ 
    std::ifstream ifs; 
    ifs.open(filename, std::ios::binary); 
    // need to spec. binary mode for Windows users
    Image src; 
    try { 
        if (ifs.fail()) { 
            throw("Can't open input file"); 
        } 
        std::string header; 
        int w, h, b; 
        ifs >> header; 
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file"); 
        ifs >> w >> h >> b; 
        src.w = w; 
        src.h = h; 
        src.pixels = new Image::Rgb[w * h]; // this is throw an exception if bad_alloc 
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
        for (int i = 0; i < w * h; ++i) { 
            ifs.read(reinterpret_cast<char *>(pix), 3); 
            src.pixels[i].r = pix[0] / 255.f; 
            src.pixels[i].g = pix[1] / 255.f; 
            src.pixels[i].b = pix[2] / 255.f; 
        } 
        ifs.close(); 
    } 
    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ifs.close(); 
    } 
 
    return src; 
}

void savePPM(const Image &img, const char *filename) 
{ 
    if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; } 
    std::ofstream ofs; 
    try { 
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
        if (ofs.fail()) throw("Can't open output file"); 
        ofs << "P6\n" << img.w << " " << img.h << "\n255\n"; 
        unsigned char r, g, b; 
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < img.w * img.h; ++i) { 
            r = static_cast<float>(std::min(1.f, img.pixels[i].r) * 255); 
            g = static_cast<float>(std::min(1.f, img.pixels[i].g) * 255); 
            b = static_cast<float>(std::min(1.f, img.pixels[i].b) * 255); 
            ofs << r << g << b; 
        } 
        ofs.close(); 
    } 
    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 
}  

void grayScale(Image &img)
{
    for (int i = 0; i < img.w * img.h; ++i)
    {
        float greyVal = 0;
        greyVal += img.pixels[i];
        Image::Rgb grayRgb(greyVal, greyVal, greyVal);
        img.pixels[i] = grayRgb; 
    }
}
 