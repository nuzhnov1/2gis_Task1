#include "distant_matrix.h"


DistantMatrix::DistantMatrix(const std::vector<double>& _data, 
                             size_t _size) noexcept : 
    m_data(_data), m_size(_size)
{
}

const double* DistantMatrix::get_data() const 
{
    return m_data.data();
}

size_t DistantMatrix::get_size() const 
{
    return m_size;
}

double DistantMatrix::get_distant(size_t i, size_t j) const 
{
    return m_data.at(i * m_size + j);
}
