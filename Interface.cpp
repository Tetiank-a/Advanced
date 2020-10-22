#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t kMd = 1000000007;

struct Edge
{
    int64_t room_from;
    int64_t room_to;
};

// Creating and reading edges
std::vector <Edge> ReadEdges(int64_t number_of_paths,
                             std::istream& input = std::cin);

// Writing a number of possible variants
void Write(int64_t variants, std::ostream& output = std::cout);

class Matrix {
 private:
    std::vector < std::vector <int64_t> > matrix_;
    int64_t size_;
 public:
    int64_t GetSize();
    Matrix(int64_t number_of_rooms, int64_t digit);
    void Create(std::vector <Edge> edges, int64_t number_of_path);
    int64_t get(int64_t i, int64_t j);
    void set(int64_t i, int64_t j, int64_t value);
};

// Matrix Multiplication
Matrix MultiplicationOfMatrices(Matrix a, Matrix b);

// Exponentiation of a matrix
Matrix MatrixInPower(Matrix a, int64_t k);

// The number of possible paths from room#0 with given length
int64_t SumCalc(Matrix a, int64_t number_of_rooms);

int64_t Run(int64_t number_of_rooms, int64_t number_of_path,
            int64_t path_length, std::vector <Edge> edges);

int64_t ReadNumber(std::istream& input = std::cin);
int64_t ReadNumber(std::istream& input);

std::vector <Edge> ReadEdges(int64_t number_of_paths, std::istream& input);

void Write(int64_t variants, std::ostream& output);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto &number_of_rooms = ReadNumber();
    const auto &number_of_path = ReadNumber();
    const auto &path_length = ReadNumber();
    const auto &edges = ReadEdges(number_of_path);
    const auto &variants = Run(number_of_rooms, number_of_path,
                               path_length, edges);
    Write(variants);

    return 0;
}
