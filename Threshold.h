#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "Filter.h"

class Threshold : public Filter {
private:
    int thresholdLimit;

public:
    Threshold(int limit);

    void apply(std::vector<std::vector<pixel>>& pixels) override;
};

#endif