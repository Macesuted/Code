/**
 * @file 6185.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod 1000000007

class Matrix {
   private:
    vector<vector<int64_t>> a;
    size_t n, m;

   public:
    Matrix(size_t _n, size_t _m) { a.resize(n = _n, vector<int64_t>(m = _m, 0)); }

    vector<int64_t>& operator[](size_t x) { return a[x]; }
    int64_t get(size_t x, size_t y) const { return a[x][y]; }

    Matrix operator*(const Matrix& b) const {
        Matrix ans(n, b.m);
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                for (size_t k = 0; k < b.m; k++) ans[i][k] = (ans[i][k] + this->get(i, j) * b.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(size_t x) const {
        Matrix a = *this, ans(n, n);
        for (size_t i = 0; i < n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

void solve(void) {
    Matrix a(1, 6), f(6, 6);
    a[0][0] = 1;

    f[0][0] = f[0][1] = f[0][2] = f[0][3] = f[0][5] = 1;
    f[1][0] = 1;
    f[2][0] = 1, f[2][5] = 1;
    f[3][0] = 1, f[3][4] = 1;
    f[4][3] = 1;
    f[5][0] = 1, f[5][2] = 1;

    int64_t n;
    while (cin >> n) cout << (a * (f ^ n))[0][0] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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