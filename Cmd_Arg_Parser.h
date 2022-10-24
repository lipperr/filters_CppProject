

#ifndef PROJECT1_CMD_ARG_PARSER_H
#define PROJECT1_CMD_ARG_PARSER_H

#include <string>
#include <vector>


struct FilterDescriptor {
    std::string_view name;
    std::vector<std::string_view> parameters;
};

class Cmd_Arg_Parser {
public:
    Cmd_Arg_Parser() = default;

    bool Parser(int argc, char *argv[]);

    void FillQuery(int argc, char *argv[]);

    std::string_view GetInputFileName() const {
        return input_file_;
    }

    std::string_view GetOutputFileName() const {
        return output_file_;
    }

    std::vector<FilterDescriptor> GetQuery() const {
        return query_;
    }

protected:
    std::string input_file_;
    std::string output_file_;
    std::vector<FilterDescriptor> query_;
};


#endif //PROJECT1_CMD_ARG_PARSER_H
