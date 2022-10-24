#include "FilterPipelineFactory.h"

namespace FilterFactories {
    BaseFilter *MakeBlurFilter(
            const FilterDescriptor &fd) {
        if (fd.parameters.size() != 1) {
            throw std::invalid_argument("one argument expected");
        }
//         здесь выкенется ошибка, если аргументы не того типа
        double sigma = 0.0;
        sigma = lexical_cast<double>(fd.parameters[0]);

        return new BlurFilter(sigma);

    }

    BaseFilter *MakeCropFilter(const FilterDescriptor &fd) {
        if (fd.parameters.size() != 2) {
            throw std::invalid_argument("two arguments expected");
        }

        // здесь выкенется ошибка, если аргументы не того типа
        size_t width = 0;
        size_t height = 0;
        width = lexical_cast<size_t>(fd.parameters[0]);
        height = lexical_cast<size_t>(fd.parameters[1]);

        return new CropFilter(width, height);

    }

    BaseFilter *MakeGsFilter(const FilterDescriptor &fd) {
        if (!fd.parameters.empty()) {
            throw std::invalid_argument("zero arguments expected");
        }
        return new GsFilter();
    }

    BaseFilter *MakeNegFilter(const FilterDescriptor &fd) {
        if (!fd.parameters.empty()) {
            throw std::invalid_argument("zero arguments expected");
        }
        return new NegFilter();
    }

    BaseFilter *MakeSharpFilter(const FilterDescriptor &fd) {
        if (!fd.parameters.empty()) {
            throw std::invalid_argument("zero arguments expected");
        }
        return new SharpFilter();
    }

    BaseFilter *MakeEdgeFilter(const FilterDescriptor &fd) {
        if (fd.parameters.size() != 1) {
            throw std::invalid_argument("one argument expected");
        }

       // здесь выкенется ошибка, если аргументы не того типа
        int32_t threshold = 0;
        threshold = lexical_cast<int32_t>(fd.parameters[1]);
        return new EdgeFilter(threshold);
    }
}


BaseFilter *FilterPipelineFactory::CreateFilter(const FilterDescriptor &fd) {
    FilterFactoryPtr creator = GetFilterCreatorByName(fd.name);
    if (!creator) {
        return nullptr;
    }

    return creator(fd);

}

FilterPipelineFactory::FilterFactoryPtr FilterPipelineFactory::GetFilterCreatorByName(std::string_view name) {
    auto it = filter_creators_.find(name);
    if (it == filter_creators_.end()) {
        return nullptr;
    }
    return it->second;
}