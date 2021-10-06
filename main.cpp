#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "arg_parser.h"
#include "calculation_methods.h"


void print_result(const std::vector<size_t>& result, double path_len);
void print_info(const std::string& _man_filename);


const std::string MANUAL_FILE_NAME = "manual.txt";


int main(int argc, char** argv) {
    std::vector<size_t> result_path;
    double result_path_len = 0.0;
    ArgParser::Arguments args;

    try 
    {
        args = ArgParser::parse_arguments(static_cast<size_t>(argc), argv);
    }
    catch (const ArgParser::bad_parse& except) 
    {
        std::cout << "Error: " << except.what() << "." << std::endl;
        
        return -1;
    }
    
    if (args.get_help_flag())
        print_info(MANUAL_FILE_NAME);
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
    for (auto iter = path.begin(); iter != path.end(); iter++) 
        std::cout << *iter + 1 << " --> ";
    std::cout << *path.begin() + 1 << "." << std::endl;

    std::cout << "Cycle length: " << path_len << "." << std::endl;
}

void print_info(const std::string& _man_filename)
{
    std::ifstream manual_file(_man_filename);
    
    while (manual_file.good())
    {
        std::string buffer;

        std::getline(manual_file, buffer);
        buffer += '\n';
        std::cout << buffer;
    }
    
    if (manual_file.bad())
    {
        std::cout << "Failed to read manual from file " 
            << '\"' << _man_filename << '\"' << std::endl;
    }
    else if (!manual_file.is_open())
    {
        std::cout << "Failed to open manual file " 
            << '\"' << _man_filename << '\"' << std::endl;
    }
}
