#ifndef BITMAP_CPP_CROPFILTER_H
#define BITMAP_CPP_CROPFILTER_H
#include "BaseFilter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter() = default;
    CropFilter(int width, int height) :  width_(width), height_(height) {}

    Bitmap* Apply(Bitmap* image) override;

protected:
    int width_ = 0;
    int height_ = 0;
};

#endif //BITMAP_CPP_CROPFILTER_H
