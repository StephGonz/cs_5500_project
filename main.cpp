#include <iostream>
#include <string>

#include "Image.hpp"

int main(int argc, char **argv)
{
    /* read test images in */
    Image cabin = readPPM("cabin.ppm");
    //Image squid = readPPM("squid.ppm");
    //Image tetons = readPPM("tetons.ppm");


    /* gray scale images */
    //grayScale(cabin);
    //grayScale(squid);
    //grayScale(tetons);

    /* red images */
    Image cabinRed(cabin, Image::kRed);
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

    savePPM(cabinRed, "cabinRed.ppm");
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