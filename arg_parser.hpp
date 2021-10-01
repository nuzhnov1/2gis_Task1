#include "distant_matrix.hpp"
#include <vector>


enum class np_type {
    none,
    complete,
    partial
};


class Arguments {

    DistantMatrix& m_matrix;
    np_type m_algo_type;
    bool m_help;
    
public:

    Arguments(DistantMatrix& _matrix, np_type _algo_type, bool _help);

    DistantMatrix& get_matrix() const;
    np_type get_algo_type() const;
    bool get_help() const;

};

Arguments parse_arguments(size_t _argc, char** _argv);
