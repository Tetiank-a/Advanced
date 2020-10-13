#include <iostream>
#include <vector>
#include <utility>
#include <map>

int64_t md = 1000000007, N;
std::vector < std::vector <int64_t> > ed;
std::vector < std::vector <int64_t> >
X(std::vector < std::vector <int64_t> > a,
    std::vector < std::vector <int64_t> > b) {
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
Pow(std::vector < std::vector <int64_t> > a, int64_t k) {
    std::vector < std::vector <int64_t> > res = ed;
    while (k) {
        if (k & 1)
            res = X(res, a);
        a = X(a, a);
        k >>= 1;
    }
    return res;
}
int main() {
    int64_t k, m, x, y, sum = 0;
    std::cin >> N >> m >> k;
    std::vector < std::vector <int64_t> > a(N);
    for (int64_t i = 0; i < N; ++i)
        for (int64_t j = 0; j < N; ++j)
            a[i].push_back(0);
    ed = a;
    for (int64_t i = 0; i < N; ++i)
        ed[i][i] = 1;
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> x >> y;
        a[x - 1][y - 1]++;
    }
    a = Pow(a, k);
    for (int64_t i = 0; i < N; ++i)
        sum = (sum + a[0][i]) % md;
    std::cout << sum;
}
