#include "distant_matrix.hpp"
#include <stdexcept>


DistantMatrix::DistantMatrix()
    : m_data(), m_size(0)
{
}

DistantMatrix::DistantMatrix(const std::vector<double>& _data, size_t size) 
    : m_data(_data), m_size(size)
{
}

DistantMatrix::DistantMatrix(const DistantMatrix& _matrix) 
    : m_data(_matrix.m_data), m_size(_matrix.m_size)
{
}

DistantMatrix& DistantMatrix::operator=(const DistantMatrix& _matrix) {
    if (this == &_matrix)
        return *this;
    
    m_data = _matrix.m_data;
    m_size = _matrix.m_size;
    
    return *this;
}

double DistantMatrix::get_distant(size_t i, size_t j) const {
    size_t index = i * m_size + j;

    return m_data.at(index);
}

size_t DistantMatrix::get_size() const {
    return m_size;
}
