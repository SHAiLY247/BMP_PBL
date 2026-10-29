#include "GrayscaleFilter.h"

void GrayscaleFilter::apply(std::vector<std::vector<pixel>>& pixels)
{
    for (int row = 0; row < pixels.size(); row++)
    {
        for (int col = 0; col < pixels[row].size(); col++)
        {
            int gray = 0.299 * pixels[row][col].red
                     + 0.587 * pixels[row][col].green
                     + 0.114 * pixels[row][col].blue;

            pixels[row][col].red = gray;
            pixels[row][col].green = gray;
            pixels[row][col].blue = gray;
        }
    }
}