#ifndef BITMAP_CPP_BASEFILTER_H
#define BITMAP_CPP_BASEFILTER_H

#include <vector>
#include <cmath>
#include "Bitmap.h"


class BaseFilter { // abstract class
public:
    virtual Bitmap *Apply(Bitmap *image) = 0;

    virtual ~BaseFilter() = default;
};


#endif //BITMAP_CPP_BASEFILTER_H
