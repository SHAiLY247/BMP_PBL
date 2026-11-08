#include <iostream>
#include <vector>
#include "CropRotate.h"

using namespace std;


// CROP IMAGE
bool cropImage(
    vector<vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int startRow, int startCol,
    int cropWidth, int cropHeight)
{
    int height = pixels.size();

    if (height == 0)
        return false;

    int width = pixels[0].size();

    // Validate crop coordinates
    if (startRow < 0 || startCol < 0 ||
        cropWidth <= 0 || cropHeight <= 0 ||
        startRow + cropHeight > height ||
        startCol + cropWidth > width)
    {
        cout << "Invalid crop dimensions or coordinates.\n";
        return false;
    }

    vector<vector<pixel>> cropped(
        cropHeight, vector<pixel>(cropWidth));

    // Copy selected pixels
    for (int r = 0; r < cropHeight; r++)
    {
        for (int c = 0; c < cropWidth; c++)
        {
            cropped[r][c] =
                pixels[startRow + r][startCol + c];
        }
    }

    // Replace original image
    pixels = cropped;

    // Update image dimensions
    infoHeader.width = cropWidth;

    if (infoHeader.height < 0)
        infoHeader.height = -cropHeight;
    else
        infoHeader.height = cropHeight;

    cout << "Image cropped successfully!\n";

    return true;
}


// ROTATE IMAGE
bool rotateImage(
    vector<vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int choice)
{
    int height = pixels.size();

    if (height == 0)
        return false;

    int width = pixels[0].size();

    vector<vector<pixel>> rotated;

    // Allocate new dimensions
    if (choice == 1 || choice == 2)
        rotated.resize(width, vector<pixel>(height));

    else if (choice == 3)
        rotated.resize(height, vector<pixel>(width));

    else
    {
        cout << "Invalid rotation choice.\n";
        return false;
    }

    // Rearrange pixels
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
                rotated[height - 1 - r][width - 1 - c]
                    = pixels[r][c];
            }
        }
    }

    pixels = rotated;

    // Update image dimensions
    infoHeader.width = width == 0 ? 0 : pixels[0].size();

    if (infoHeader.height < 0)
        infoHeader.height = -(int)pixels.size();
    else
        infoHeader.height = pixels.size();

    cout << "Image rotated successfully!\n";

    return true;
}