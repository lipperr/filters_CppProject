#include "Application.h"


void Application::FiltersToApply() {
    std::vector<FilterDescriptor> query = income.GetQuery();
    for (const auto &descr: query) {
        BaseFilter *filter = fpf.CreateFilter(descr);
        pipeline_.push_back(filter);
    }
}


void Application::RegisterFilterFactories() {
    fpf.AddFilterCreator("-blur", FilterFactories::MakeBlurFilter);
    fpf.AddFilterCreator("-crop", FilterFactories::MakeCropFilter);
    fpf.AddFilterCreator("-gs", FilterFactories::MakeGsFilter);
    fpf.AddFilterCreator("-neg", FilterFactories::MakeNegFilter);
    fpf.AddFilterCreator("-edge", FilterFactories::MakeEdgeFilter);
    fpf.AddFilterCreator("-sharp", FilterFactories::MakeSharpFilter);
}


Bitmap *Application::Do() {
    Bitmap *image0;
    for (auto filter: pipeline_) {
        image0 = filter->Apply(image);
        image = image0;
    }
    return image;
}

