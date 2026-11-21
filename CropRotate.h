#ifndef CROPROTATE_H
#define CROPROTATE_H

#include <vector>
#include "BMPHandler.h"

bool cropImage(
    std::vector<std::vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int startRow, int startCol,
    int cropWidth, int cropHeight
);

bool rotateImage(
    std::vector<std::vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader,
    int choice
);

#endif