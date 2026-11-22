#include <vector>
#include "CropRotate.h"

using namespace std;

bool cropImage(
    vector<vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int startRow, int startCol,
    int cropWidth, int cropHeight)
{
    int height = static_cast<int>(pixels.size());
    if (height == 0)
        return false;

    int width = static_cast<int>(pixels[0].size());

    // Validate crop bounds
    if (startRow < 0 || startCol < 0 ||
        cropWidth <= 0 || cropHeight <= 0 ||
        startRow + cropHeight > height ||
        startCol + cropWidth > width)
    {
        return false;
    }

    vector<vector<pixel>> cropped(cropHeight, vector<pixel>(cropWidth));

    // pixels[0] is already top row thanks to loadBMP
    for (int r = 0; r < cropHeight; r++)
    {
        for (int c = 0; c < cropWidth; c++)
        {
            cropped[r][c] = pixels[startRow + r][startCol + c];
        }
    }

    pixels = cropped;

    infoHeader.width = cropWidth;
    infoHeader.height = (infoHeader.height < 0) ? -cropHeight : cropHeight;

    return true;
}

bool rotateImage(
    vector<vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int choice)
{
    int height = static_cast<int>(pixels.size());
    if (height == 0)
        return false;

    int width = static_cast<int>(pixels[0].size());
    vector<vector<pixel>> rotated;

    if (choice == 1 || choice == 2)
        rotated.resize(width, vector<pixel>(height));
    else if (choice == 3)
        rotated.resize(height, vector<pixel>(width));
    else
        return false;

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (choice == 1)
            {
                // 90 degrees clockwise
                rotated[c][height - 1 - r] = pixels[r][c];
            }
            else if (choice == 2)
            {
                // 90 degrees anticlockwise
                rotated[width - 1 - c][r] = pixels[r][c];
            }
            else if (choice == 3)
            {
                // 180 degrees
                rotated[height - 1 - r][width - 1 - c] = pixels[r][c];
            }
        }
    }

    pixels = rotated;

    int newWidth = static_cast<int>(pixels[0].size());
    int newHeight = static_cast<int>(pixels.size());

    infoHeader.width = newWidth;
    infoHeader.height = (infoHeader.height < 0) ? -newHeight : newHeight;

    return true;
}