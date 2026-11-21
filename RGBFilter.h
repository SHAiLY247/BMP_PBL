#ifndef RGBFILTER_H
#define RGBFILTER_H

#include "Filter.h"

enum class Channel
{
    Red,
    Green,
    Blue
};

class RGBFilter : public Filter
{
private:
    Channel selectedChannel;

public:
    RGBFilter(Channel channel);
    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif