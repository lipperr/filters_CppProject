#include "Cmd_Arg_Parser.h"

static size_t MIN_ARGS = 4;
static size_t INPUT_FILE_IDX = 2;
static size_t OUTPUT_FILE_IDX = 3;

bool Cmd_Arg_Parser::Parser(int argc, char **argv) {
    if (argc < MIN_ARGS) {
        return false; // вернуть справку (требования, названия фильтров, параметры)
    }
    input_file_ = argv[INPUT_FILE_IDX];
    output_file_ = argv[OUTPUT_FILE_IDX];

    FillQuery(argc, argv);

    return true;
}

void Cmd_Arg_Parser::FillQuery(int argc, char **argv) {
    size_t i = OUTPUT_FILE_IDX + 1;
    while (i < argc) {
        if (argv[i][0] == '-') {
            FilterDescriptor new_filter;
            new_filter.name = argv[i];
            ++i;
            while (i < argc && argv[i][0] != '-') {
                new_filter.parameters.emplace_back(argv[i]);
                ++i;
            }
            query_.push_back(new_filter);
        } else {
            ++i;
        }
    }
}


