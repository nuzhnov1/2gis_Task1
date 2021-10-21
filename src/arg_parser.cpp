#include "arg_parser.h"

#include <cstdio>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>


using bad_parse = ArgParser::bad_parse;
using Algorithm = ArgParser::Algorithm;
using Arguments = ArgParser::Arguments;


std::shared_ptr<DistantMatrix> _parse_matrix(char* filename);
bool _is_sqr(double num);
Algorithm _parse_algo_type(char* arg);


bad_parse::bad_parse(const std::string& what) noexcept :
    std::exception(), m_what(what)
{
}

bad_parse::bad_parse(const char* what) noexcept :
    std::exception(), m_what(what)
{
}

bad_parse::bad_parse(const bad_parse& other) noexcept :
    std::exception(other), m_what(other.m_what)
{
}

const char* bad_parse::what() const noexcept 
{
    return m_what.c_str();
}


Arguments::Arguments(char* progname, 
    const std::shared_ptr<DistantMatrix>& matrix_ptr, Algorithm algo,
    bool help_flag
) noexcept :

    m_progname(progname), m_matrix_ptr(std::move(matrix_ptr)), m_algo(algo),
    m_help_flag(help_flag)
{
}

const char* Arguments::get_progname() const
{
    return m_progname;
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


Arguments ArgParser::parse_arguments(size_t argc, char** argv) 
{
    char* progname = argv[0];
    std::shared_ptr<DistantMatrix> matrix_ptr = nullptr;
    Algorithm algo = Algorithm::brute_force;
    bool help_flag = false;

    // skip first commands argument - program name
    for (size_t i = 1; i < argc; i++) 
    {
        char* arg = argv[i];

        // parse single dash arguments
        if (arg[0] == '-') 
        {
            char singe_dash_arg = arg[1];

            switch (singe_dash_arg)
            {
            case 'f':
            {
                i++;
                if (i >= argc)
                {
                    throw bad_parse("data file is not specified " 
                        "for parameter \"-f\"");
                }

                matrix_ptr = _parse_matrix(argv[i]);
                break;
            }
            case 'm':
            {
                i++;
                if (i >= argc)
                {
                    throw bad_parse("calculation mode is not set "
                        "for parameter \"-m\"");
                }
                
                algo = _parse_algo_type(argv[i]);
                break;
            }
            case 'h':
            {
                matrix_ptr = nullptr;
                help_flag = true;
                
                return Arguments(progname, matrix_ptr, algo, help_flag);
            }
            default:
            {
                char message[1024];

                snprintf(message, 1024, "unknown parameter \"%s\"", arg);
                throw bad_parse(message);
            }
            }
        }
        else
        {
            char message[1024];
            
            snprintf(message, 1024, "unknown parameter \"%s\"", arg);
            throw bad_parse(message);
        }
    }

    if (matrix_ptr == nullptr)
        help_flag = true;

    return Arguments(progname, matrix_ptr, algo, help_flag);
}

std::shared_ptr<DistantMatrix> _parse_matrix(char* filename) 
{
    std::ifstream stream(filename);
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
        char message[1024];

        snprintf(message, 1024, "failed to read file \"%s\"", filename);
        throw bad_parse(message);
    }
    else if (!stream.is_open())
        throw bad_parse("failed to open the specifed file");
    else
        throw bad_parse("missing terminating 0 in the specifed file");
}

Algorithm _parse_algo_type(char* arg) 
{
    if (arg == "np_complete")
        return Algorithm::brute_force;
    else if (arg == "np_partial")
        return Algorithm::nearest_neighbour;
    else
    {
        char message[1024];

        snprintf(message, 1024, "unknown calculation mode \"%s\"", arg);
        throw bad_parse(message);
    }
}

bool _is_sqr(double num) 
{
    size_t sqr = 0;

    for (size_t i = 1; sqr + 2 <= num; i += 2)
        sqr += i;
    
    return num == sqr || num == 1;
}
