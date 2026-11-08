#include "RGBFilter.h"

RGBFilter::RGBFilter(Channel channel)
{
    selectedChannel = channel;
}

void RGBFilter::apply(std::vector<std::vector<pixel>>& pixels)
{
    for (int row = 0; row < pixels.size(); row++)
    {
        for (int col = 0; col < pixels[row].size(); col++)
        {
            if (selectedChannel == Channel::Red)
            {
                pixels[row][col].green = 0;
                pixels[row][col].blue = 0;
            }
            else if (selectedChannel == Channel::Green)
            {
                pixels[row][col].red = 0;
                pixels[row][col].blue = 0;
            }
            else if (selectedChannel == Channel::Blue)
            {
                pixels[row][col].red = 0;
                pixels[row][col].green = 0;
            }
        }
    }
}