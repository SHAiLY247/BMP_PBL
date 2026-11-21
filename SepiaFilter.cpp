#include "SepiaFilter.h"

void SepiaFilter::apply(std::vector<std::vector<pixel>>& pixels)
{
    for (int row = 0; row < pixels.size(); row++)
    {
        for (int col = 0; col < pixels[row].size(); col++)
        {
            int r = pixels[row][col].red;
            int g = pixels[row][col].green;
            int b = pixels[row][col].blue;

            int newRed = 0.393 * r + 0.769 * g + 0.189 * b;
            int newGreen = 0.349 * r + 0.686 * g + 0.168 * b;
            int newBlue = 0.272 * r + 0.534 * g + 0.131 * b;

            if (newRed > 255) newRed = 255;
            if (newGreen > 255) newGreen = 255;
            if (newBlue > 255) newBlue = 255;

            pixels[row][col].red = newRed;
            pixels[row][col].green = newGreen;
            pixels[row][col].blue = newBlue;
        }
    }
}