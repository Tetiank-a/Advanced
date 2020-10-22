#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t md = 1000000007;

// Class for a Matrix
class Matrix {
 private:
    std::vector < std::vector <int64_t> > matrix;
    int64_t Size;
 public:
    int64_t GetSize();
    Matrix(int64_t N, int64_t x);
    void Read(int64_t M);
    int64_t get(int64_t i, int64_t j);
    void set(int64_t i, int64_t j, int64_t value);
};

// Getting the size of the Matrix
int64_t Matrix::GetSize();

// Creating a Matrix N*N with 0
Matrix::Matrix(int64_t N, int64_t x);

// Reading the Matrix
void Matrix::Read(int64_t M);

// Getter
int64_t Matrix::get(int64_t i, int64_t j);

// Setter
void Matrix::set(int64_t i, int64_t j, int64_t value);

// Matrix Multiplication
Matrix Multiplication(Matrix a, Matrix b);

// Matrix in Power (Uses a function of Multiplication)
Matrix InPower(Matrix a, int64_t k);

// Calculating an answer for vertex 0
int64_t Sum_calc(Matrix a, int64_t N);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t N, M, K;
    std::cin >> N >> M >> K;
    Matrix a(N, 0);
    a.Read(M);
    a = InPower(a, K);
    std::cout << Sum_calc(a, N);
    return 0;
}
