#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H

#include "Filter.h"

class GrayscaleFilter : public Filter
{
public:
    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif