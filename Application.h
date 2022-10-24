#ifndef BITMAP_CPP_APPLICATION_H
#define BITMAP_CPP_APPLICATION_H

#include <vector>
#include "BaseFilter.h"
#include "BlurFilter.h"
#include "CropFilter.h"
#include "NegFilter.h"
#include "EdgeFilter.h"
#include "GsFilter.h"
#include "SharpFilter.h"
#include "Bitmap.h"
#include "Cmd_Arg_Parser.h"
#include "FilterPipelineFactory.h"


class Application {
public:
    Application() = default;

    // fills filter_creators in FilterPipelineFactory with names and pointers to existing filters
    void RegisterFilterFactories();

    // fills the pipeline vector
    void FiltersToApply();

    // this method literally applies filters to the given image and returns changed bitmap file
    Bitmap *Do();

public:
    // section for public fields
    Cmd_Arg_Parser income;
    Bitmap *image = new Bitmap;

protected:
    std::vector<BaseFilter *> pipeline_;
    FilterPipelineFactory fpf;
};


#endif //BITMAP_CPP_APPLICATION_H
