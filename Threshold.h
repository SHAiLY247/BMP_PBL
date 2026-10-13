#pragma once
#include <vector>
#include <cstdint>
struct Pixel { //whole to be deleted when files will be merged and pixel struct or similar will already be in gurveen's file 
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};
class Threshold {
private:
    int thresholdLimit;
public:
    Threshold(int limit);
    void applyFilter(std::vector<std::vector<Pixel>>& imageMatrix);
};