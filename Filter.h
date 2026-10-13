#ifndef FILTER_H
#define FILTER_H
#include <vector>
#include "BMPHandler.h"
class Filter
{
 public:
       virtual void apply(std::vector<std::vector<pixel>>& pixels)=0;
       virtual ~Filter() {}
};
#endif