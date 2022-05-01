/**
 * @file 100.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define mod 1000000007

template <typename T>
class Matrix {
   private:
    vector<vector<T>> a;
    int n, m;

   public:
    vector<T>& operator[](int x) { return a[x]; }
    T get(int x, int y) const { return a[x][y]; }
    void resize(int _n, int _m) { return a.resize(n = _n, vector<T>(m = _m, 0)); }
    Matrix operator*(const Matrix& o) const {
        assert(m == o.n);
        Matrix ans;
        ans.resize(n, o.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < o.m; j++)
                for (int k = 0; k < m; k++) ans[i][j] = (ans[i][j] + this->get(i, k) * o.get(k, j)) % mod;
        return ans;
    }
    Matrix operator^(int x) const {
        assert(n == m);
        Matrix ans, a = *this;
        ans.resize(n, n);
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

void solve(void) {
    int n, p, m;
    cin >> n >> p >> m;
    Matrix<int64_t> A, B;
    A.resize(n, p), B.resize(p, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++) cin >> A[i][j], A[i][j] = (A[i][j] % mod + mod) % mod;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < m; j++) cin >> B[i][j], B[i][j] = (B[i][j] % mod + mod) % mod;
    Matrix<int64_t> C = A * B;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << C[i][j] << ' ';
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}