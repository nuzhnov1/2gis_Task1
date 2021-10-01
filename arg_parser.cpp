#include "arg_parser.hpp"

#include <string>
#include <cmath>


static DistantMatrix _parse_matrix(size_t& _cur_arg, size_t _argc, char** _argv);
static bool _is_sqr(double _num);
static np_type _parse_algo_type(char* _arg);


Arguments::Arguments(DistantMatrix& _matrix, np_type _algo_type, bool _help) :
    m_matrix(_matrix), m_algo_type(_algo_type), m_help(_help)
{
}

DistantMatrix& Arguments::get_matrix() const {
    return m_matrix;
}

np_type Arguments::get_algo_type() const {
    return m_algo_type;
}

bool Arguments::get_help() const {
    return m_help;
}

Arguments parse_arguments(size_t _argc, char** _argv) {
    DistantMatrix* matrix_ptr = nullptr;
    np_type algo_type = np_type::none;
    bool help = false;
    
    for (size_t i = 0; i < _argc; i++) {
        std::string arg(_argv[i]);

        if (arg[0] == '-') {
            char singe_dash_arg = arg[1];

            switch (singe_dash_arg)
            {
            case 'f':
            {
                matrix_ptr = &_parse_matrix(i, _argc, _argv);
                break;
            }
            case 'm':
            {
                i++;
                if (i >= _argc)
                    ; // wrong input: calculation mode is not set
                
                algo_type = _parse_algo_type(_argv[i + 1]);
                break;
            }
            case 'h':
            {
                help = true;
                break;
            }
            default:
            {
                ;   // wrong input: unknown parameter arg
                break;
            }
            }
        }
        else
            ; // wrong input: unknown parameter arg
    }
}

DistantMatrix _parse_matrix(size_t& _cur_arg, size_t _argc, char** _argv) {
    std::vector<double> distants;

    // skip the initial argument "0"
    for (_cur_arg++; _cur_arg < _argc; _cur_arg++) {
        std::string arg(_argv[_cur_arg]);
        double dist = std::stod(arg);

        if (dist == 0.0) {
            size_t count = distants.size();
            if (_is_sqr(count)) {
                size_t size = static_cast<size_t>(sqrt(count));
                return DistantMatrix(distants, size);
            }
            else
                ; // throw exception, because input array it's not matrix
        }
        else
            distants.push_back(dist);
    }

    // wrong input: missing terminating 0
}

bool _is_sqr(double _num) {
    size_t sqr = 0;

    for (size_t i = 1; sqr + 2 <= _num; i += 2)
        sqr += i;
    
    return _num == sqr || _num == 1;
}

np_type _parse_algo_type(char* _arg) {
    std::string arg(_arg);

    if (arg == "np_complete") 
        return np_type::complete;
    else if (arg == "np_partial")
        return np_type::partial;
    else
        ; // wrong input: unknown calculation mode
}
