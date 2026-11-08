#include "InversionFilter.h"

void InversionFilter::apply(std::vector<std::vector<pixel>>& pixels)
{
    for (int row = 0; row < pixels.size(); row++)
    {
        for (int col = 0; col < pixels[row].size(); col++)
        {
            pixels[row][col].red = 255 - pixels[row][col].red;
            pixels[row][col].green = 255 - pixels[row][col].green;
            pixels[row][col].blue = 255 - pixels[row][col].blue;
        }
    }
}