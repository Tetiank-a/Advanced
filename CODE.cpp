#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t kMd = 1000000007;

struct Edge
{
    int64_t vertex_from;
    int64_t vertex_to;
};

// Reading numbers
int64_t ReadNumber(std::istream& input = std::cin);

// Creating and reading edges
std::vector <Edge> ReadEdges(int64_t number_of_edges,
                             std::istream& input = std::cin);

// Writing a number of possible variants
void Write(int64_t variants, std::ostream& output = std::cout);

class Matrix {
 private:
    std::vector < std::vector <int64_t> > matrix_;
    int64_t size_;
 public:
    int64_t GetSize();
    Matrix(int64_t matrix_size, int64_t digit);
    Matrix(std::vector <Edge> edges, int64_t matrix_size,
           int64_t number_of_edges);
    int64_t get(int64_t i, int64_t j);
    void set(int64_t i, int64_t j, int64_t value);
};

int64_t Matrix::GetSize() {
    return this->size_;
}

// Creating an identity matrix N*N
Matrix::Matrix(int64_t matrix_size, int64_t digit) {
    std::vector <int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_[i][i] = digit;
    this->size_ = matrix_size;
}

Matrix::Matrix(std::vector <Edge> edges, int64_t matrix_size,
               int64_t number_of_edges) {
    this->size_ = matrix_size;
    std::vector <int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);

    int64_t x, y;
    for (int64_t i = 0; i < number_of_edges; ++i) {
        this->matrix_[edges[i].vertex_from - 1][edges[i].vertex_to - 1]++;
    }
}

int64_t Matrix::get(int64_t i, int64_t j) {
    return this->matrix_[i][j];
}

void Matrix::set(int64_t i, int64_t j, int64_t value) {
    this->matrix_[i][j] = value;
}

// Matrix Multiplication
Matrix MultiplicationOfMatrices(Matrix a, Matrix b) {
    int64_t N = a.GetSize();
    Matrix c(N, 0);
    for (int64_t i = 0; i < N; ++i)
        for (int64_t j = 0; j < N; ++j) {
            c.set(i, j, 0);
            for (int64_t k = 0; k < N; ++k)
                c.set(i, j, (a.get(i, k) * b.get(k, j) % kMd +
                      c.get(i, j)) % kMd);
        }
    return c;
}

// Exponentiation of a matrix
Matrix MatrixInPower(Matrix a, int64_t k) {
    int64_t N = a.GetSize();
    Matrix res(N, 1);
    while (k) {
        if (k & 1)
            res = MultiplicationOfMatrices(res, a);
        a = MultiplicationOfMatrices(a, a);
        k >>= 1;
    }
    return res;
}

// The number of possible paths from room#0 with given length
int64_t SumCalculation(Matrix matrix, int64_t matrix_size) {
    int64_t sum = 0;
    for (int64_t i = 0; i < matrix_size; ++i)
        sum = (sum + matrix.get(0, i)) % kMd;
    return sum;
}

int64_t CountNumberOfVariants(int64_t number_of_rooms, int64_t number_of_edges,
            int64_t path_length, std::vector <Edge> edges) {
    Matrix rooms_matrix(edges, number_of_rooms, number_of_edges);
    rooms_matrix = MatrixInPower(rooms_matrix, path_length);
    return SumCalculation(rooms_matrix, number_of_rooms);
}

int64_t ReadNumber(std::istream& input) {
    int value;
    input >> value;
    return value;
}

std::vector <Edge> ReadEdges(int64_t number_of_edges, std::istream& input) {
    int64_t x, y;
    std::vector <Edge> edges;
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

void Write(int64_t variants, std::ostream& output) {
    output << variants << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto &number_of_rooms = ReadNumber();
    const auto & number_of_edges = ReadNumber();
    const auto &path_length = ReadNumber();
    const auto &edges = ReadEdges(number_of_edges);
    const auto &variants = CountNumberOfVariants(number_of_rooms,
                                                 number_of_edges,
                                                 path_length, edges);
    Write(variants);

    return 0;
}
