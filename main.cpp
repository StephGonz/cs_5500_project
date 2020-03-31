#include <iostream>
#include <string>

#include "Image.hpp"

int main(int argc, char **argv)
{
    /* read test images in */
    //Image cabin = readPPM("./data/cabin.PPM");
    //Image squid = readPPM("./data/squid.PPM");
    //Image squid2 = readPPM("./data/squid.PPM");
    //Image tetons = readPPM("tetons.ppm");

    //Image::Rgb s2 = squid2(10, 10);
    //std::cout << "regular squid pix @ 10, 10: " << s2.r << s2.g << s2.b << std::endl;

    /* gray scale images */
    //grayScale(cabin);
    //grayScale(squid);

    //Image::Rgb s1 = squid(10, 10);
    //squid2(10, 10) = squid(10, 10);
    //squid2(10, 10).r = 99.9;
    //s2 = squid2(10, 10);
    //std::cout << "regular squid pix @ 10, 10: " << s2.r << s2.g << s2.b << std::endl;
    //std::cout << "grey squid pix @ 10, 10: " << s1.r << s1.g << s1.b << std::endl;
    //grayScale(tetons);

    /* red images */
    //Image cabinRed(cabin, Image::kRed);
    //Image squidRed(squid, Image::kRed);
    //Image tetonsRed(tetons, Image::kRed);

    /* green images */
    //Image cabinGreen(cabin, Image::kGreen);
    //Image squidGreen(squid, Image::kGreen);
    //Image tetonsGreen(tetons, Image::kGreen);

    /* blue images */
    //Image cabinBlue(cabin, Image::kBlue);
    //Image squidBlue(squid, Image::kBlue);
    //Image tetonsBlue(tetons, Image::kBlue);


    /* save the images*/
    //savePPM(cabin, "cabinGray.ppm");
    //savePPM(squid, "squidGray.ppm");
    //savePPM(tetons, "tetonsGray.ppm");

    //savePPM(cabinRed, "./output/cabinRed.PPM");
    //savePPM(squidRed, "squidRed.ppm");
    //savePPM(tetonsRed, "tetonsRed.ppm");

    //savePPM(cabinGreen, "cabinGreen.ppm");
    //savePPM(squidGreen, "squidGreen.ppm");
    //savePPM(tetonsGreen, "tetonsGreen.ppm");

    //savePPM(cabinBlue, "cabinBlue.ppm");
    //savePPM(squidBlue, "squidBlue.ppm");
    //savePPM(tetonsBlue, "tetonsBlue.ppm");

    return 0;
}
