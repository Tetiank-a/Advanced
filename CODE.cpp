#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t MODULE = 1000000007;

struct Edge
{
    int64_t vertex_from;
    int64_t vertex_to;
};

// Reading numbers
int64_t ReadNumber(std::istream& input = std::cin);

// Creating and reading edges
std::vector<Edge> ReadEdges(const int64_t &number_of_edges,
    std::istream& input = std::cin);

// Writing a number of possible variants
void Write(const int64_t &variants, std::ostream& output = std::cout);

class Matrix {
 private:
    std::vector< std::vector<int64_t> > matrix_;
    int64_t size_;
 public:
    int64_t GetSize() const;
    Matrix(const int64_t& matrix_size, const int64_t& digit);
    Matrix(const std::vector<Edge> &edges, const int64_t &matrix_size,
           const int64_t &number_of_edges);
    int64_t get(const int64_t & vertex_first,
                const int64_t & vertex_second) const;
    void set(const int64_t &vertex_first, const int64_t &vertex_second,
             const int64_t &value);
};

int64_t Matrix::GetSize() const {
    return this->size_;
}

// Creating an identity matrix N*N
Matrix::Matrix(const int64_t &matrix_size, const int64_t &digit) {
    const std::vector<int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_[i][i] = digit;
    this->size_ = matrix_size;
}

Matrix::Matrix(const std::vector<Edge>& edges, const int64_t& matrix_size,
               const int64_t& number_of_edges) {
    this->size_ = matrix_size;
    std::vector<int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);

    for (int64_t i = 0; i < number_of_edges; ++i) {
        this->matrix_[edges[i].vertex_from - 1][edges[i].vertex_to - 1]++;
    }
}

int64_t Matrix::get(const int64_t& vertex_first,
                    const int64_t& vertex_second) const {
    return this->matrix_[vertex_first][vertex_second];
}

void Matrix::set(const int64_t& vertex_first, const int64_t& vertex_second,
                 const int64_t& value) {
    this->matrix_[vertex_first][vertex_second] = value;
}

// Matrix Multiplication
Matrix MultiplicationOfMatrices(const Matrix &matrix_first,
                                const Matrix &matrix_second) {
    const int64_t matrix_size = matrix_first.GetSize();
    Matrix matrix_result(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        for (int64_t j = 0; j < matrix_size; ++j) {
            matrix_result.set(i, j, 0);
            for (int64_t k = 0; k < matrix_size; ++k)
                matrix_result.set(i, j, (matrix_first.get(i, k) *
                    matrix_second.get(k, j) % MODULE +
                    matrix_result.get(i, j)) % MODULE);
        }
    return matrix_result;
}

// Exponentiation of a matrix
Matrix MatrixInPower(Matrix matrix, int64_t power) {
    const int64_t matrix_size = matrix.GetSize();
    Matrix result_matrix(matrix_size, 1);
    while (power) {
        if (power & 1)
            result_matrix = MultiplicationOfMatrices(result_matrix, matrix);
        matrix = MultiplicationOfMatrices(matrix, matrix);
        power >>= 1;
    }
    return result_matrix;
}

// The number of possible paths from room#0 with given length
int64_t SumCalculation(const Matrix &matrix, const int64_t &matrix_size) {
    int64_t sum = 0;
    for (int64_t i = 0; i < matrix_size; ++i)
        sum = (sum + matrix.get(0, i)) % MODULE;
    return sum;
}

int64_t CountNumberOfVariants(const int64_t &number_of_rooms,
                              const int64_t &number_of_edges,
                              const int64_t &path_length,
                              const std::vector<Edge> &edges) {
    Matrix rooms_matrix(edges, number_of_rooms, number_of_edges);
    rooms_matrix = MatrixInPower(rooms_matrix, path_length);
    return SumCalculation(rooms_matrix, number_of_rooms);
}

int64_t ReadNumber(std::istream& input) {
    int value;
    input >> value;
    return value;
}

std::vector<Edge> ReadEdges(const int64_t &number_of_edges,
                            std::istream& input) {
    int64_t x, y;
    std::vector<Edge> edges;
    for (int64_t i = 0; i < number_of_edges; ++i)
    {
        input >> x >> y;
        Edge path;
        path.vertex_from = x;
        path.vertex_to = y;
        edges.push_back(path);
    }
    return edges;
}

void Write(const int64_t &variants, std::ostream& output) {
    output << variants << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto& number_of_rooms = ReadNumber();
    const auto& number_of_edges = ReadNumber();
    const auto& path_length = ReadNumber();
    const auto& edges = ReadEdges(number_of_edges);
    const auto& variants = CountNumberOfVariants(number_of_rooms,
        number_of_edges,
        path_length, edges);
    Write(variants);

    return 0;
}
