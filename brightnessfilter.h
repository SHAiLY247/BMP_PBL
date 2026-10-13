#ifndef BRIGHTNESSFILTER_H
#define BRIGHTNESSFILTER_H

#include "Filter.h"

class BrightnessFilter : public Filter
{
private:
    int brightnessValue;

public:
    BrightnessFilter(int value);

    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif