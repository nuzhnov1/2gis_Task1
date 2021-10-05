#ifndef DISTANT_MATRIX_H
#define DISTANT_MATRIX_H


#include <vector>


class DistantMatrix 
{

    std::vector<double> m_data;
    size_t              m_size;

public:

    explicit DistantMatrix() noexcept = default;
    explicit DistantMatrix(const std::vector<double>& data,
                           size_t size) noexcept;
    DistantMatrix(const DistantMatrix& other) noexcept = default;

    DistantMatrix& operator=(const DistantMatrix& matrix) = default;

    const double* get_data() const;
    size_t get_size() const;

    double get_distant(size_t i, size_t j) const;
};


#endif
