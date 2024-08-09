/**
 * @file 7512.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define maxn 105

typedef pair<int, int> pii;

class Matrix {
   private:
    vector<vector<int64_t>> a;
    int n, m;

   public:
    void resize(int _n, int _m) { return a.resize(n = _n, vector<int64_t>(m = _m, 0)); }
    vector<int64_t>& operator[](size_t x) { return a[x]; }
    int64_t get(int x, int y) const { return a[x][y]; }
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
    void print(void) {
        cerr << "### Print" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cerr << a[i][j] << ' ';
            cerr << endl;
        }
        return;
    }
};

vector<vector<pii>> F, G;

void solve(void) {
    int n, m;
    int64_t L, R;
    cin >> n >> m >> L >> R;
    F.clear(), F.resize(n + 1), G.clear(), G.resize(n + 1);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        (v <= n ? F : G)[u].emplace_back(v <= n ? v : v - n, w);
    }
    Matrix baseF;
    baseF.resize(n + 1, n + 1);
    for (int i = n; i; i--) {
        baseF[i][i] = 1;
        for (auto [x, w] : F[i])
            for (int j = 1; j <= n; j++) baseF[i][j] = (baseF[i][j] + w * baseF[x][j]) % mod;
    }
    Matrix baseG;
    baseG.resize(n + 1, n + 1);
    for (int i = 1; i <= n; i++)
        for (auto [j, w] : G[i])
            for (int k = j; k <= n; k++) baseG[i][k] = (baseG[i][k] + w * baseF[j][k]) % mod;
    for (int i = 0; i <= n; i++) baseG[i][0] = 1;
    Matrix A;
    A.resize(1, n + 1);
    for (int i = 0; i <= n; i++) A[0][i] = baseF[1][i];
    int64_t t = (L - 1) / n;
    if (t) L -= t * n, R -= t * n, A = A * (baseG ^ t);
    int64_t ans = 0;
    for (int i = 0; i < L; i++) ans = (ans + mod - A[0][i]) % mod;
    t = (R - 1) / n;
    if (t) L -= t * n, R -= t * n, A = A * (baseG ^ t);
    for (int i = 0; i <= R; i++) ans = (ans + A[0][i]) % mod;
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}