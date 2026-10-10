#ifndef FILTER_H
#define FILTER_H

#include "BMPHandler.h"
#include<vector>

class Filter
{
public:
    virtual void apply(std::vector<std::vector<pixel>>& pixels) = 0;

    virtual ~Filter() = default;
};

#endif