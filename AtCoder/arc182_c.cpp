/**
 * @file arc182_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod 998244353

const int prime[6] = {2, 3, 5, 7, 11, 13};

class Matrix {
   private:
    vector<vector<int64_t>> a;
    int n, m;

   public:
    void resize(int _n, int _m) { return a.resize(n = _n, vector<int64_t>(m = _m, 0)); }

    vector<int64_t>& operator[](size_t x) { return a[x]; }
    int64_t get(int x, int y) const { return a[x][y]; }

    Matrix operator+(const Matrix& o) const {
        Matrix ans = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ans[i][j] = (ans[i][j] + o.get(i, j)) % mod;
        return ans;
    }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        ans.resize(n, o.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < o.m; k++) ans[i][k] = (ans[i][k] + this->get(i, j) * o.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(int64_t x) const {
        Matrix a = *this, ans;
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
    int64_t n, m;
    cin >> n >> m;
    Matrix base;
    base.resize(65, 65);
    base[63][64] = base[64][64] = 1;
    for (int i = 1; i <= m; i++) {
        int own = 0, cnt[6] = {0, 0, 0, 0, 0, 0}, v = i;
        for (int j = 0; j < 6; j++)
            while (v % prime[j] == 0) own |= 1 << j, cnt[j]++, v /= prime[j];
        Matrix F;
        F.resize(65, 65);
        for (int S = 0; S < 64; S++) {
            int O = 0;
            for (int i = 0; i < 6; i++)
                if ((S >> i & 1) && (own >> i & 1)) O |= 1 << i;
            for (int T = 0; T < 64; T++)
                if ((T & O) == T) {
                    int coef = 1;
                    for (int i = 0; i < 6; i++)
                        if (T >> i & 1) coef *= cnt[i];
                    assert(F[S ^ T][S] == 0);
                    F[S ^ T][S] = coef;
                }
        }
        base = base + F;
    }
    Matrix A;
    A.resize(1, 65);
    for (int i = 0; i < 64; i++) A[0][i] = 1;
    A = A * (base ^ (n + 1));
    cout << (A[0][64] + mod - 1) % mod << endl;
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