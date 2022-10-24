#ifndef BITMAP_CPP_BLURFILTER_H
#define BITMAP_CPP_BLURFILTER_H
#include "BaseFilter.h"

class BlurFilter : public BaseFilter {
public:
    BlurFilter() = default;
    explicit BlurFilter(double sigma) : sigma_(sigma) {}

    Bitmap* Apply(Bitmap* image) override;

protected:

    double sigma_ = 0;
    double C = 1.0 / (sigma_ * std::sqrt(2 * M_PI));
};


#endif //BITMAP_CPP_BLURFILTER_H
