#ifndef BITMAP_CPP_SHARPFILTER_H
#define BITMAP_CPP_SHARPFILTER_H
#include "BaseFilter.h"

class SharpFilter : public BaseFilter {
public:
    Bitmap* Apply(Bitmap* image) override;
};



#endif //BITMAP_CPP_SHARPFILTER_H
