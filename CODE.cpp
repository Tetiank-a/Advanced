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
int64_t ReadNumber(std::istream& input = std::cin) {
    int64_t value;
    input >> value;
    return value;
}

// Creating and reading edges
std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input = std::cin) {
    std::vector<Edge> edges(number_of_edges);

    for (int64_t i = 0; i < number_of_edges; ++i) {
        input >> edges[i].vertex_from >> edges[i].vertex_to;
    }

    return edges;
}

// Writing a number of possible variants
void Write(const int64_t& ways, std::ostream& output = std::cout) {
    output << ways << '\n';
}

class Matrix {
 protected:
    std::vector< std::vector<int64_t> > matrix_;
    int64_t number_of_strings_;
    int64_t number_of_columns_;

 public:
     Matrix() {
         number_of_strings_ = 0;
         number_of_columns_ = 0;
     }

    Matrix(const int64_t& number_of_strings,
           const int64_t& number_of_columns) {
        std::vector< std::vector<int64_t> > matrix(number_of_strings,
            std::vector<int64_t>(number_of_columns, 0));
        matrix_ = matrix;
        number_of_strings_ = number_of_strings;
        number_of_columns_ = number_of_columns;
    }

    explicit Matrix(const std::vector< std::vector<int64_t> >& matrix) {
        matrix_ = matrix;
        number_of_strings_ = matrix.size();
        number_of_columns_ = matrix[0].size();
    }

    int64_t Get(const int64_t& line,
                const int64_t& column) const {
        if (line < 0 || line >= number_of_strings_ || column < 0 ||
            column >= number_of_columns_) {
            throw std::runtime_error("Indexes of matrix are out of range");
        }
        return matrix_[line][column];
    }

    void Set(const int64_t& line,
             const int64_t& column,
             const int64_t& value) {
        if (line < 0 || line >= number_of_strings_ || column < 0 ||
            column >= number_of_columns_) {
            throw std::runtime_error("Indexes of matrix are out of range");
        }

        matrix_[line][column] = value;
    }

    // Matrix Multiplication
    Matrix Multiplication(const Matrix& matrix_right) {
        const int64_t& strings_left_matrix =
            this->GetNumberOfStrings();
        const int64_t& columns_left_matrix =
            this->GetNumberOfColumns();
        const int64_t& strings_right_matrix =
            matrix_right.GetNumberOfStrings();
        const int64_t& columns_right_matrix =
            matrix_right.GetNumberOfColumns();

        if (columns_left_matrix != strings_right_matrix) {
            throw std::runtime_error("Multiplication is impossible");
        }

        Matrix matrix_result(strings_left_matrix, columns_right_matrix);

        for (int64_t i = 0; i < strings_left_matrix; ++i) {
            for (int64_t j = 0; j < columns_right_matrix; ++j) {
                for (int64_t k = 0; k < columns_left_matrix; ++k) {
                    const int64_t left_cell = this->Get(i, k);
                    const int64_t right_cell = matrix_right.Get(k, j);
                    const int64_t result_cell = matrix_result.Get(i, j);
                    const int64_t result_cell_updated = ((left_cell *
                        right_cell) % MODULUS + result_cell) % MODULUS;

                    matrix_result.Set(i, j, result_cell_updated);
                }
            }
        }

        return matrix_result;
    }

    int64_t GetNumberOfStrings() const {
        return number_of_strings_;
    }

    int64_t GetNumberOfColumns() const {
        return number_of_columns_;
    }
};

class SquareMatrix : public Matrix {
 public:
     SquareMatrix(const int64_t& number_of_strings,
                  const int64_t& number_of_columns, const bool& digit) :
         Matrix(number_of_strings, number_of_columns) {
         if (digit == true) {
             for (int i = 0; i < number_of_strings; ++i) {
                 matrix_[i][i] = 1;
             }
         }
     }
     SquareMatrix(const std::vector<Edge>& edges, const int64_t& size) {
         std::vector< std::vector<int64_t> > matrix(size,
             std::vector<int64_t>(size, 0));

         for (int64_t i = 0; i < edges.size(); ++i) {
             const int first_vertex = edges[i].vertex_from - INDEX_SHIFT;
             const int second_vertex = edges[i].vertex_to - INDEX_SHIFT;
             if (first_vertex < 0 || first_vertex >= size ||
                 second_vertex < 0 || second_vertex >= size) {
                 throw std::runtime_error("Indexes of matrix are out of range");
             }
             matrix[first_vertex][second_vertex]++;
         }

         matrix_ = matrix;
         number_of_strings_ = size;
         number_of_columns_ = size;
     }

     explicit SquareMatrix(const Matrix& matrix) {
         if (matrix.GetNumberOfStrings() != matrix.GetNumberOfColumns()) {
             throw std::runtime_error("Impossible to create a Square Matrix");
         }
         std::vector< std::vector<int64_t> > square_matrix(
             matrix.GetNumberOfStrings(),
             std::vector<int64_t>(matrix.GetNumberOfColumns(), 0));
         for (int i = 0; i < matrix.GetNumberOfStrings(); ++i)
             for (int j = 0; j < matrix.GetNumberOfColumns(); ++j) {
                 square_matrix[i][j] = matrix.Get(i, j);
             }
         matrix_ = square_matrix;
         number_of_strings_ = matrix.GetNumberOfStrings();
         number_of_columns_ = matrix.GetNumberOfColumns();
     }

     Matrix Convert_to_Matrix() {
         std::vector< std::vector<int64_t> > matrix(
             number_of_strings_,
             std::vector<int64_t>(number_of_columns_, 0));
         for (int i = 0; i < this->number_of_strings_; ++i)
             for (int j = 0; j < number_of_columns_; ++j) {
                 matrix[i][j] = matrix_[i][j];
             }
         const Matrix result_matrix(matrix);
         return result_matrix;
     }

     SquareMatrix Multiplication(SquareMatrix matrix_right_square) {
         Matrix matrix_left = this->Convert_to_Matrix();
         const Matrix matrix_right = matrix_right_square.Convert_to_Matrix();
         const Matrix result_matrix = matrix_left.Multiplication(matrix_right);
         SquareMatrix result_square_matrix = SquareMatrix(result_matrix);
         return result_square_matrix;
     }

     // Exponentiation of a matrix
     SquareMatrix MatrixInPower(int64_t power) {
         SquareMatrix delta_matrix = *this;
         SquareMatrix result_matrix(delta_matrix.GetNumberOfStrings(),
             delta_matrix.GetNumberOfColumns(), true);
         while (power != 0) {
             if (power % 2 != 0) {
                 result_matrix = result_matrix.Multiplication(delta_matrix);
             }
             delta_matrix = delta_matrix.Multiplication(delta_matrix);
             power /= 2;
         }
         return result_matrix;
     }
};

int64_t CountNumberOfWays(const int64_t& number_of_rooms,
                          const int64_t& path_length,
                          const std::vector<Edge>& edges) {
    SquareMatrix rooms_matrix(edges, number_of_rooms);
    const SquareMatrix result_matrix = rooms_matrix.MatrixInPower(path_length);
    int64_t sum = 0;

    for (int64_t i = 0; i < number_of_rooms; ++i) {
        sum = (sum + result_matrix.Get(0, i)) % MODULUS;
    }

    return sum;
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
