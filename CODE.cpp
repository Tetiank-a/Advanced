#include <iostream>
#include <vector>
#include <utility>

const int64_t MODULUS = 1000000007;
const int64_t INDEX_SHIFT = 1;

struct Edge {
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
    int64_t number_of_strings_;
    int64_t number_of_columns_;

 public:
     Matrix(const int64_t& number_of_strings, const int64_t& number_of_columns,
            const bool& digit) {
         std::vector< std::vector<int64_t> > matrix(number_of_strings,
             std::vector<int64_t>(number_of_columns, 0));
         if (digit) {
             if (number_of_strings != number_of_columns) {
                 std::cout << "Impossible to create an identity matrix";
                 exit(0);
             }
             for (int i = 0; i < number_of_strings; ++i) {
                 matrix[i][i] = 1;
             }
         }
         matrix_ = matrix;
         number_of_strings_ = number_of_strings;
         number_of_columns_ = number_of_columns;
     }

     Matrix(const std::vector<Edge>& edges, const int64_t& size) {
         std::vector< std::vector<int64_t> > matrix(size,
             std::vector<int64_t>(size, 0));

         for (int64_t i = 0; i < edges.size(); ++i) {
             const int first_vertex = edges[i].vertex_from - INDEX_SHIFT;
             const int second_vertex = edges[i].vertex_to - INDEX_SHIFT;
             matrix[first_vertex][second_vertex]++;
         }

         matrix_ = matrix;
         number_of_strings_ = size;
         number_of_columns_ = size;
     }

     int64_t Get(const int64_t& line,
                 const int64_t& column) const {
         if (line < 0 || line >= number_of_strings_ || column < 0 ||
             column >= number_of_columns_) {
             std::cout << "Indexes of matrix are out of range";
             exit(0);
         }

         return matrix_[line][column];
     }

     void Set(const int64_t& line,
              const int64_t& column,
              const int64_t& value) {
         if (line < 0 || line >= number_of_strings_ || column < 0 ||
             column >= number_of_columns_) {
             std::cout << "Indexes of matrix are out of range";
             exit(0);
         }

         matrix_[line][column] = value;
     }

     int64_t GetNumberOfStrings() const {
         return number_of_strings_;
     }

     int64_t GetNumberOfColumns() const {
         return number_of_columns_;
     }
};

// Matrix Multiplication
Matrix MultiplicationOfMatrices(const Matrix& matrix_left,
                                const Matrix& matrix_right) {
    const int64_t& strings_left_matrix = matrix_left.GetNumberOfStrings();
    const int64_t& columns_left_matrix = matrix_left.GetNumberOfColumns();
    const int64_t& strings_right_matrix = matrix_right.GetNumberOfStrings();
    const int64_t& columns_right_matrix = matrix_right.GetNumberOfColumns();

    if (columns_left_matrix != strings_right_matrix) {
        std::cout << "Multiplication of matrixes is impossible";
        exit(0);
    }

    Matrix matrix_result(strings_left_matrix, columns_right_matrix, false);

    for (int64_t i = 0; i < strings_left_matrix; ++i) {
        for (int64_t j = 0; j < columns_right_matrix; ++j) {
            for (int64_t k = 0; k < columns_left_matrix; ++k) {
                const int64_t left_cell = matrix_left.Get(i, k);
                const int64_t right_cell = matrix_right.Get(k, j);
                const int64_t result_cell = matrix_result.Get(i, j);
                const int64_t result_cell_updated = ((left_cell * right_cell) %
                                                      MODULUS + result_cell) %
                                                      MODULUS;

                matrix_result.Set(i, j, result_cell_updated);
            }
        }
    }

    return matrix_result;
}

// Exponentiation of a matrix
Matrix MatrixInPower(const Matrix& matrix, int64_t power) {
    Matrix delta_matrix = matrix;
    Matrix result_matrix(delta_matrix.GetNumberOfStrings(),
                         delta_matrix.GetNumberOfColumns(), true);

    while (power) {
        if (power % 2 != 0) {
            result_matrix = MultiplicationOfMatrices(result_matrix,
                                                     delta_matrix);
        }
        delta_matrix = MultiplicationOfMatrices(delta_matrix, delta_matrix);
        power /= 2;
    }

    return result_matrix;
}

int64_t CountNumberOfWays(const int64_t& number_of_rooms,
                          const int64_t& path_length,
                          const std::vector<Edge>& edges) {
    const Matrix rooms_matrix(edges, number_of_rooms);
    const Matrix result_matrix = MatrixInPower(rooms_matrix, path_length);
    int64_t sum = 0;

    for (int64_t i = 0; i < number_of_rooms; ++i) {
        sum = (sum + result_matrix.Get(0, i)) % MODULUS;
    }

    return sum;
}

int64_t ReadNumber(std::istream& input) {
    int64_t value;
    input >> value;
    return value;
}

std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input) {
    std::vector<Edge> edges;

    for (int64_t i = 0; i < number_of_edges; ++i) {
        Edge path;
        input >> path.vertex_from >> path.vertex_to;
        edges.push_back(path);
    }

    return edges;
}

void Write(const int64_t& ways, std::ostream& output) {
    output << ways << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto& number_of_rooms = ReadNumber();
    const auto& number_of_edges = ReadNumber();
    const auto& path_length = ReadNumber();
    const auto& edges = ReadEdges(number_of_edges);
    const auto& ways = CountNumberOfWays(number_of_rooms, path_length, edges);

    Write(ways);

    return 0;
}
