#include "distant_matrix.h"


DistantMatrix::DistantMatrix(const std::vector<double>& data, 
    size_t size) noexcept :
     
    m_data(data), m_size(size)
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
