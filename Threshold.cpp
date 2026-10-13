#include "Threshold.h"

Threshold::Threshold(int limit) {
    thresholdLimit = limit;
}

void Threshold::apply(
    std::vector<std::vector<pixel>>& imageMatrix
) {
    for (auto& row : imageMatrix) {
        for (auto& p : row) {
            int average = (p.red + p.green + p.blue) / 3;

            unsigned char value =
                (average >= thresholdLimit) ? 255 : 0;

            p.red = value;
            p.green = value;
            p.blue = value;
        }
    }
}