#include "Threshold.h"
Threshold::Threshold(int limit) {
    thresholdLimit = limit;
}
void Threshold::applyFilter(std::vector<std::vector<Pixel>>& imageMatrix) {
    for (int i = 0; i < imageMatrix.size(); i++) {
        for (int j = 0; j < imageMatrix[i].size(); j++) {
            Pixel& currentPixel = imageMatrix[i][j];
            int average = (currentPixel.red + currentPixel.green + currentPixel.blue) / 3;
            if (average >= thresholdLimit) {
                currentPixel.red = 255;
                currentPixel.green = 255;
                currentPixel.blue = 255;
            } else {
                currentPixel.red = 0;
                currentPixel.green = 0;
                currentPixel.blue = 0;
            }
        }
    }
}