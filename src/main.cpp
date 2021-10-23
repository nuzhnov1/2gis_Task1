#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>

#include "arg_parser.h"
#include "calculation_methods.h"


void print_result(const std::vector<size_t>& result, double path_len);
void print_manual(const char* progname);


constexpr auto MANUAL_FILENAME = "manual.txt";


int main(int argc, char** argv) {
    std::vector<size_t> result_path;
    double result_path_len = 0.0;
    ArgParser::Arguments args;

    try 
    {
        args = ArgParser::parse_arguments(static_cast<size_t>(argc), argv);
    }
    catch (const std::exception& except) 
    {
        std::cout << "Error: " << except.what() << "." << std::endl;
        
        return -1;
    }
    
    if (args.get_help_flag())
        print_manual(args.get_progname());
    else
    {
        std::pair<std::vector<size_t>, double> result;

        if (args.get_algorithm() == ArgParser::Algorithm::brute_force)
            result = brute_force(*args.get_matrix());
        else
            result = nearest_neighbour(*args.get_matrix());

        result_path = result.first;
        result_path_len = result.second;

        print_result(result_path, result_path_len);
    }

    return 0;
}

void print_result(const std::vector<size_t>& path, double path_len) 
{
    std::cout << "Result: ";
    for (auto& iter : path) 
        std::cout << iter + 1 << " --> ";
    std::cout << path[0] + 1 << "." << std::endl;

    std::cout << "Cycle length: " << path_len << "." << std::endl;
}

void print_manual(const char* _progname)
{
#if defined(_WIN32)
    char path_delim = '\\';
#elif defined(__unix__)
    char path_delim = '/';
#endif

    // characters number of path without manual filename
    std::string progname(_progname);
    size_t n = progname.find_last_of(path_delim);
    std::string man_filename = 
        std::string(progname.begin(), progname.begin() + n + 1) +
        MANUAL_FILENAME;

    // open manual file
    std::ifstream manual_file(man_filename);
    
    // reads every line in the file and prints it to standard output
    while (manual_file.good())
    {
        std::string buffer;

        std::getline(manual_file, buffer);
        buffer += '\n';
        std::cout << buffer;
    }
    
    if (manual_file.bad())
    {
        printf("Failed to read manual from file \"%s\".\n",
            man_filename.c_str());
    }
    else if (!manual_file.is_open())
        printf("Failed to open manual file \"%s\".\n", man_filename.c_str());
}
