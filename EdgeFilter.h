#ifndef BITMAP_CPP_EDGEFILTER_H
#define BITMAP_CPP_EDGEFILTER_H
#include "BaseFilter.h"

class EdgeFilter : public BaseFilter {
public:
    EdgeFilter() = default;
    explicit EdgeFilter(int32_t threshold) : threshold_(threshold) {}

    Bitmap* Apply(Bitmap* image) override;

protected:
    int32_t threshold_ = 0;
};


#endif //BITMAP_CPP_EDGEFILTER_H
