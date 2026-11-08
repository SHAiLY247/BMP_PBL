#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H

#include "Filter.h"

class SepiaFilter : public Filter
{
public:
    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif