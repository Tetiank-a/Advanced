#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t md = 1000000007;

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
int64_t Matrix::GetSize() {
    return this->Size;
}

// Creating a Matrix N*N with 0
Matrix::Matrix(int64_t N, int64_t x) {
    std::vector <int64_t> str(N, 0);
    for (int64_t i = 0; i < N; ++i)
        this->matrix.push_back(str);
    for (int64_t i = 0; i < N; ++i)
        this->matrix[i][i] = x;
    this->Size = N;
}

// Reading the Matrix
void Matrix::Read(int64_t M) {
    int64_t x, y;
    for (int64_t i = 0; i < M; ++i) {
        std::cin >> x >> y;
        this->matrix[x - 1][y - 1]++;
    }
}

// Getter
int64_t Matrix::get(int64_t i, int64_t j) {
    return this->matrix[i][j];
}

// Setter
void Matrix::set(int64_t i, int64_t j, int64_t value) {
    this->matrix[i][j] = value;
}

// Matrix Multiplication
Matrix Multiplication(Matrix a, Matrix b) {
    int64_t N = a.GetSize();
    Matrix c(N, 0);
    for (int64_t i = 0; i < N; ++i)
        for (int64_t j = 0; j < N; ++j) {
            c.set(i, j, 0);
            for (int64_t k = 0; k < N; ++k)
                c.set(i, j, (a.get(i, k) * b.get(k, j) % md +
                      c.get(i, j)) % md);
        }
    return c;
}

// Matrix in Power
Matrix InPower(Matrix a, int64_t k) {
    int64_t N = a.GetSize();
    Matrix res(N, 1);
    while (k) {
        if (k & 1)
            res = Multiplication(res, a);
        a = Multiplication(a, a);
        k >>= 1;
    }
    return res;
}

// Calculating an answer for vertex 0
int64_t Sum_calc(Matrix a, int64_t N) {
    int64_t sum = 0;
    for (int64_t i = 0; i < N; ++i)
        sum = (sum + a.get(0, i)) % md;
    return sum;
}

// Reading and solving
void Run() {
    int64_t N, M, K;
    std::cin >> N >> M >> K;
    Matrix a(N, 0);
    a.Read(M);
    a = InPower(a, K);
    std::cout << Sum_calc(a, N);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Run();
    return 0;
}
