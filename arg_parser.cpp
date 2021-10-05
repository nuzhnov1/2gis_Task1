#include "arg_parser.h"

#include <fstream>
#include <cmath>
#include <vector>
#include <string>


using bad_parse = ArgParser::bad_parse;
using Algorithm = ArgParser::Algorithm;
using Arguments = ArgParser::Arguments;


std::shared_ptr<DistantMatrix> _parse_matrix(const char* _filename);
bool _is_sqr(double num);
Algorithm _parse_algo_type(char* arg);


bad_parse::bad_parse(const std::string& _what) noexcept :
    m_what(_what)
{
}

bad_parse::bad_parse(const char* _what) noexcept :
    m_what(_what)
{
}

bad_parse::bad_parse(const bad_parse& _other) noexcept :
    m_what(_other.m_what)
{
}

const char* bad_parse::what() const noexcept 
{
    return m_what.c_str();
}


Arguments::Arguments(std::shared_ptr<DistantMatrix>& _matrix_ptr,
                     Algorithm _algo, bool _help_flag) noexcept :
    m_matrix_ptr(std::move(_matrix_ptr)), m_algo(_algo),
    m_help_flag(_help_flag)
{
}

std::shared_ptr<DistantMatrix> Arguments::get_matrix() const 
{
    return m_matrix_ptr;
}

Algorithm Arguments::get_algorithm() const 
{
    return m_algo;
}

bool Arguments::get_help_flag() const 
{
    return m_help_flag;
}


Arguments ArgParser::parse_arguments(size_t _argc, char** _argv) 
{
    std::shared_ptr<DistantMatrix> matrix_ptr = nullptr;
    Algorithm algo = Algorithm::brute_force;
    bool help_flag = false;

    // skip first commands argument - program name
    for (size_t i = 1; i < _argc; i++) 
    {
        std::string arg(_argv[i]);

        // parse single dash arguments
        if (arg[0] == '-') 
        {
            char singe_dash_arg = arg[1];

            switch (singe_dash_arg)
            {
            case 'f':
            {
                i++;
                if (i >= _argc)
                {
                    throw bad_parse(
                        "data file is not specified " 
                        "for parameter \"-f\"");
                }

                matrix_ptr = _parse_matrix(_argv[i]);
                break;
            }
            case 'm':
            {
                i++;
                if (i >= _argc)
                {
                    throw bad_parse(
                        "calculation mode is not set "
                        "for parameter \"-m\"");
                }
                
                algo = _parse_algo_type(_argv[i]);
                break;
            }
            case 'h':
            {
                matrix_ptr = nullptr;
                help_flag = true;
                
                return Arguments(matrix_ptr, algo, help_flag);
            }
            default:
            {
                std::string message = 
                    std::string("unknown parameter ") + std::string("\"") + 
                    arg + std::string("\"");

                throw bad_parse(message);
            }
            }
        }
        else
        {
            std::string message = 
                std::string("unknown parameter ") + std::string("\"") + 
                arg + std::string("\"");

            throw bad_parse(message);
        }
    }

    if (matrix_ptr == nullptr)
        help_flag = true;

    return Arguments(matrix_ptr, algo, help_flag);
}

std::shared_ptr<DistantMatrix> _parse_matrix(const char* _filename) 
{
    std::ifstream stream(_filename);
    std::vector<double> distants;
    double dist = 0.0;

    stream >> dist;  // skip the preceding whitespace and initial 0
    
    while (stream.good()) 
    {
        stream >> dist; // extract distant value and skip preceding whitespace

        if (dist == 0.0) 
        {
            size_t count = distants.size();

            // checking whether the data array is a matrix
            if (_is_sqr(count)) 
            {
                size_t size = static_cast<size_t>(sqrt(count));
                return std::shared_ptr<DistantMatrix>(
                    new DistantMatrix(distants, size));
            }
            else
                throw bad_parse("the extracted data is not a square matrix");
        }
        else
            distants.push_back(dist);
    }
    
    if (stream.bad())
    {
        std::string message = 
            std::string("failed to read file ") + std::string("\"") + 
            std::string(_filename) + std::string("\"");
         
        throw bad_parse(message);
    }
    else
        throw bad_parse("missing terminating 0 in the specifed file");
}

Algorithm _parse_algo_type(char* _arg) 
{
    std::string arg(_arg);

    if (arg == "np_complete")
        return Algorithm::brute_force;
    else if (arg == "np_partial")
        return Algorithm::nearest_neighbour;
    else
    {
        std::string message = 
            std::string("unknown calculation mode ") + std::string("\"") + 
            arg + std::string("\"");
            
        throw bad_parse(message);
    }
}

bool _is_sqr(double _num) 
{
    size_t sqr = 0;

    for (size_t i = 1; sqr + 2 <= _num; i += 2)
        sqr += i;
    
    return _num == sqr || _num == 1;
}
