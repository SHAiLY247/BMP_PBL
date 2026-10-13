#ifndef CONTRASTFILTER_H
#define CONTRASTFILTER_H

#include "Filter.h"

class ContrastFilter : public Filter
{
private:
    double contrastFactor;

public:
    ContrastFilter(double factor);

    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif