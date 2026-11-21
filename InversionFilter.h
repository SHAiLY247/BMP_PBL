#ifndef INVERSIONFILTER_H
#define INVERSIONFILTER_H
#include "Filter.h"
class InversionFilter : public Filter
{
public:
    void apply(std::vector<std::vector<pixel>>& pixels) override;
};
#endif