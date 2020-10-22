#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t md = 1000000007;
std::vector < std::vector <int64_t> > ed;

std::vector < std::vector <int64_t> >
Multiplication(std::vector < std::vector <int64_t> > a,
    std::vector < std::vector <int64_t> > b, int64_t N) {
    std::vector < std::vector <int64_t> > c = ed;
    for (int64_t i = 0; i < N; ++i)
        for (int64_t j = 0; j < N; ++j) {
            c[i][j] = 0;
            for (int64_t k = 0; k < N; ++k)
                c[i][j] = (a[i][k] * b[k][j] % md + c[i][j]) % md;
        }
    return c;
}

std::vector < std::vector <int64_t> >
Pow(std::vector < std::vector <int64_t> > a, int64_t k, int64_t N) {
    std::vector < std::vector <int64_t> > res = ed;
    while (k) {
        if (k & 1)
            res = Multiplication(res, a, N);
        a = Multiplication(a, a, N);
        k >>= 1;
    }
    return res;
}

void Creating_Ed(int64_t N) {
    std::vector <int64_t> str(N, 0);
    for (int64_t i = 0; i < N; ++i)
        ed.push_back(str);
    for (int64_t i = 0; i < N; ++i)
        ed[i][i] = 1;
}

void Creating_Main(std::vector < std::vector <int64_t> >* a,
                   int64_t N, int64_t m) {
    int64_t x, y;
    for (int64_t i = 0; i < N; ++i)
        for (int64_t j = 0; j < N; ++j)
            (*a)[i].push_back(0);
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> x >> y;
        (*a)[x - 1][y - 1]++;
    }
}

int64_t Sum_calc(std::vector < std::vector <int64_t> > a, int64_t N) {
    int64_t sum = 0;
    for (int64_t i = 0; i < N; ++i)
        sum = (sum + a[0][i]) % md;
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t k, m, sum = 0, N;

    std::cin >> N >> m >> k;

    std::vector < std::vector <int64_t> > a(N);
    Creating_Main(&a, N, m);

    Creating_Ed(N);

    a = Pow(a, k, N);
    sum = Sum_calc(a, N);

    std::cout << sum;
    return 0;
}
