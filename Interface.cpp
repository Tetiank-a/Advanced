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
std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input = std::cin);

// Writing a number of possible variants
void Write(const int64_t& ways, std::ostream& output = std::cout);

class Matrix {
 private:
    std::vector< std::vector<int64_t> > matrix_;
    int64_t size_;
 public:
    int64_t GetSize() const;
    Matrix(const int64_t& matrix_size, const int64_t& digit);
    Matrix(const std::vector<Edge>& edges, const int64_t& matrix_size);
    int64_t get(const int64_t& vertex_first,
                const int64_t& vertex_second) const;
    void set(const int64_t& vertex_first, const int64_t& vertex_second,
             const int64_t& value);
};

// Matrix Multiplication
Matrix MultiplicationOfMatrices(const Matrix& matrix_first,
                                const Matrix& matrix_second);

// Exponentiation of a matrix
Matrix MatrixInPower(const Matrix& matrix, int64_t power);

// The number of possible paths from room#0 with given length
int64_t SumCalculation(const Matrix& matrix, const int64_t& matrix_size);

int64_t CountNumberOfWays(const int64_t& number_of_rooms,
                          const int64_t& number_of_edges,
                          const int64_t& path_length,
                          const std::vector<Edge>& edges);

int64_t ReadNumber(std::istream& input);

std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input);

void Write(const int64_t& ways, std::ostream& output);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto& number_of_rooms = ReadNumber();
    const auto& number_of_edges = ReadNumber();
    const auto& path_length = ReadNumber();
    const auto& edges = ReadEdges(number_of_edges);
    const auto& ways = CountNumberOfWays(number_of_rooms,
                                         number_of_edges,
                                         path_length, edges);
    Write(ways);

    return 0;
}
