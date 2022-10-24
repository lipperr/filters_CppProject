#ifndef BITMAP_CPP_FILTERPIPELINEFACTORY_H
#define BITMAP_CPP_FILTERPIPELINEFACTORY_H

#include <map>
#include <string_view>
#include <sstream>
#include "BaseFilter.h"
#include "BlurFilter.h"
#include "CropFilter.h"
#include "NegFilter.h"
#include "EdgeFilter.h"
#include "GsFilter.h"
#include "SharpFilter.h"
#include "Cmd_Arg_Parser.h"

namespace FilterFactories {
    using FilterFactoryPtr = BaseFilter *(*)(const FilterDescriptor &fd);

    BaseFilter *MakeBlurFilter(const FilterDescriptor &fd);

    BaseFilter *MakeCropFilter(const FilterDescriptor &fd);

    BaseFilter *MakeGsFilter(const FilterDescriptor &fd);

    BaseFilter *MakeNegFilter(const FilterDescriptor &fd);

    BaseFilter *MakeSharpFilter(const FilterDescriptor &fd);

    BaseFilter *MakeEdgeFilter(const FilterDescriptor &fd);


    // функция преобразования типа аргумента
    template<typename T1, typename T2>
    T1 lexical_cast(const T2 &t2) {
        std::stringstream s;
        s << t2;
        T1 t1;
        if (s >> t1 && s.eof()) {
            return t1;
        } else {
            throw std::invalid_argument("wrong type of argument");
        }
    }
}

class FilterPipelineFactory {
public:
    using FilterFactoryPtr = BaseFilter *(*)(const FilterDescriptor &fd);
    using filter_to_factory_map = std::map<std::string_view, FilterFactoryPtr>;

    void AddFilterCreator(std::string_view name, FilterFactoryPtr pointer) {
        filter_creators_.insert(std::pair{name, pointer});
    }

    // obtains a filter descriptor and tries to create an appropriate filter object according to its current configuration
    BaseFilter *CreateFilter(const FilterDescriptor &fd);

    // helper method that gives a filter factory (filter creator)
    // from a list of registered filter factories by the given filter name.
    // A proper filter factory is a pointer to a corresponding factory method (such as MakeBlurFilter), that is,
    // we can return a nullptr if no corresponding factory method found
    FilterFactoryPtr GetFilterCreatorByName(std::string_view name);

protected:
    filter_to_factory_map filter_creators_;
};


#endif //BITMAP_CPP_FILTERPIPELINEFACTORY_H


