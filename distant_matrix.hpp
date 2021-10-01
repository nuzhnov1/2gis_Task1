#include <vector>


class DistantMatrix {

    std::vector<double> m_data;
    size_t              m_size;

public:

    DistantMatrix();
    DistantMatrix(const std::vector<double>& _data, size_t _size);
    DistantMatrix(const DistantMatrix& _matrix);

    DistantMatrix& operator=(const DistantMatrix& _matrix);

    double get_distant(size_t _i, size_t _j) const;
    size_t get_size() const;

};
