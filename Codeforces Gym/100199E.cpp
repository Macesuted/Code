/**
 * @file 100199E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

int mod;

class Matrix {
   private:
    vector<vector<int>> mat;
    int n, m;

   public:
    vector<int>& operator[](size_t i) { return mat[i]; }
    int get(size_t i, size_t j) const { return mat[i][j]; }

    void resize(int _n, int _m) { return mat.resize(n = _n, vector<int>(m = _m, 0)); }

    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        assert(a.m == b.n);

        Matrix c;
        c.resize(a.n, b.m);
        for (int i = 0; i < a.n; i++)
            for (int k = 0; k < b.m; k++) {
                int64_t ans = 0;
                for (int j = 0; j < a.m; j++) ans += a.get(i, j) * b.get(j, k);
                c.mat[i][k] = ans % mod;
            }

        return c;
    }
};

void solve(void) {
    string n;
    int m;
    cin >> n >> m >> mod;
    reverse(n.begin(), n.end());

    Matrix a, f;
    a.resize(1, 1 << m), f.resize(1 << m, 1 << m);

    for (int i = 0; i < (1 << m); i++) a[0][i] = 1;
    for (int S = 0; S < (1 << m); S++)
        for (int T = 0; T < (1 << m); T++) {
            f[S][T] = 1;
            for (int j = 1; j < m; j++)
                if ((S >> (j - 1) & 1) == (S >> j & 1) && (T >> (j - 1) & 1) == (T >> j & 1) && (S >> j & 1) == (T >> j & 1))
                    f[S][T] = 0;
        }

    {
        int p = 0;
        while (n[p] == '0') p++;
        n[p]--;
        while (p) n[--p] = '9';
        while (n.back() == '0') n.pop_back();
    }

    while (!n.empty()) {
        if ((n.front() - '0') & 1) a = a * f;
        f = f * f;
        for (int i = (int)n.size() - 1; ~i; i--) {
            if (i && (n[i] - '0') & 1) n[i - 1] += 10;
            n[i] = '0' + ((n[i] - '0') >> 1);
        }
        while (n.back() == '0') n.pop_back();
    }

    int64_t ans = 0;
    for (int i = 0; i < (1 << m); i++) ans += a.get(0, i);
    cout << ans % mod << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("nice.in", "r", stdin), freopen("nice.out", "w", stdout);
#endif
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