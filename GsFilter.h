#ifndef BITMAP_CPP_GSFILTER_H
#define BITMAP_CPP_GSFILTER_H
#include "BaseFilter.h"
class GsFilter : public BaseFilter {
public:
    Bitmap* Apply(Bitmap* image) override;
};


#endif //BITMAP_CPP_GSFILTER_H
