#ifndef ARG_PARSER_H
#define ARG_PARSER_H


#include <string>
#include <memory>
#include <exception>

#include "distant_matrix.h"


namespace ArgParser 
{
    enum class Algorithm 
    {
        brute_force,
        nearest_neighbour
    };


    class bad_parse: public std::exception 
    {
        
        std::string m_what;

    public:

        bad_parse(const std::string& what) noexcept;
        bad_parse(const char* what) noexcept;
        bad_parse(const bad_parse& other) noexcept;

        bad_parse& operator=(const bad_parse& other) noexcept = default;

        virtual const char* what() const noexcept override;
    };


    class Arguments 
    {
        
        char*                           m_progname;
        std::shared_ptr<DistantMatrix>  m_matrix_ptr;
        Algorithm                       m_algo;
        bool                            m_help_flag;

    public:

        Arguments() noexcept = default;
        Arguments(char* progname,
            const std::shared_ptr<DistantMatrix>& matrix_ptr, Algorithm algo, 
            bool help_flag) noexcept;
        Arguments(const Arguments&) = default;

        Arguments& operator=(const Arguments&) = default;

        const char* get_progname() const;
        std::shared_ptr<DistantMatrix> get_matrix() const;
        Algorithm get_algorithm() const;
        bool get_help_flag() const;

    };

    Arguments parse_arguments(size_t argc, char** argv);
}


#endif
