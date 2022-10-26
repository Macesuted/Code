/**
 * @file 108.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxk 105
#define mod 998244353

class Matrix {
   private:
    vector<vector<int>> a;

   public:
    int n, m;

    vector<int>& operator[](size_t x) { return a[x]; }
    int get(int x, int y) const { return a[x][y]; }
    void resize(int _n, int _m) { return a.resize(n = _n, vector<int>(m = _m, 0)); }
    Matrix operator*(const Matrix& o) const {
        assert(m == o.n);
        Matrix ans;
        ans.resize(n, o.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < o.m; k++) ans[i][k] = (ans[i][k] + (int64_t)this->get(i, j) * o.get(j, k)) % mod;
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

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

void solve(void) {
    int n, k;
    cin >> n >> k;
    Matrix base, f;
    base.resize(1, k + 2), base[0][0] = 1;
    f.resize(k + 2, k + 2), f[k][0] = f[k][k + 1] = f[k + 1][k + 1] = 1;
    for (int i = 0, a, b; i < k; i++) {
        cin >> a >> b, a = a * Inv(b) % mod;
        f[i][0] = f[i][k + 1] = a, f[i][i + 1] = (1 + mod - a) % mod;
    }
    base = base * (f ^ n);
    cout << base[0][k + 1] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("card.in", "r", stdin), freopen("card.out", "w", stdout);
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