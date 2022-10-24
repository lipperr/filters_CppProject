#include "Application.h"


// args: name, input image address, output image address, '-' + 'filter name' + parameters for filters
int main(int argc, char *argv[]) {
    Application app;
    bool error_catch = app.income.Parser(argc, argv);
    if (!error_catch) {
        throw std::invalid_argument("not enough command line arguments to use the application");
    }

    app.RegisterFilterFactories();
    app.FiltersToApply();
    error_catch = app.image->LoadFromFile(app.income.GetInputFileName());
    if (!error_catch) {
        throw std::invalid_argument("cannot read file");
    }

    Bitmap *image1 = app.Do();
    image1->Upload(app.income.GetOutputFileName());
    return 0;
}




