#ifndef BITMAP_CPP_NEGFILTER_H
#define BITMAP_CPP_NEGFILTER_H
#include "BaseFilter.h"

class NegFilter : public BaseFilter {
public:
    Bitmap* Apply(Bitmap* image) override;
};


#endif //BITMAP_CPP_NEGFILTER_H
