#include "brightnessfilter.h"

BrightnessFilter::BrightnessFilter(int value)
{
    brightnessValue = value;
}
void BrightnessFilter::apply(std::vector<std::vector<pixel>>& pixels)
{
    for (int row = 0; row < pixels.size(); row++)
    {
        for (int col = 0; col < pixels[row].size(); col++)
        {
            int newBlue = pixels[row][col].blue + brightnessValue;
            int newGreen = pixels[row][col].green + brightnessValue;
            int newRed = pixels[row][col].red + brightnessValue;

            if (newBlue > 255) newBlue = 255;
            if (newBlue < 0) newBlue = 0;

            if (newGreen > 255) newGreen = 255;
            if (newGreen < 0) newGreen = 0;

            if (newRed > 255) newRed = 255;
            if (newRed < 0) newRed = 0;

            pixels[row][col].blue = (unsigned char)newBlue;
            pixels[row][col].green = (unsigned char)newGreen;
            pixels[row][col].red = (unsigned char)newRed;
        }
    }
}