#ifndef CROPROTATE_H
#define CROPROTATE_H

#include <vector>
#include "BMPHandler.h"

// Pure pixel-level crop (startRow=0 is top row, startCol=0 is left column)
bool cropImage(
    std::vector<std::vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int startRow, int startCol,
    int cropWidth, int cropHeight);

// Pure pixel-level rotate (1 = 90 CW, 2 = 90 CCW, 3 = 180)
bool rotateImage(
    std::vector<std::vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int choice);

#endif