/**
 * @file agc013_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-15
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

#define maxm 100005
#define mod 1000000007

class Matrix {
   private:
    int64_t a[3][3];

   public:
    Matrix(void) { memset(a, 0, sizeof(a)); }
    int64_t* operator[](const size_t x) { return a[x]; }
    int64_t get(const size_t x, const size_t y) const { return a[x][y]; }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++) ans[i][k] = (ans[i][k] + this->get(i, j) * o.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(int x) const {
        Matrix ans, a = *this;
        ans[0][0] = ans[1][1] = ans[2][2] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

int a[maxm];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    Matrix ans, base, pbase;
    base[0][0] = 1, base[1][0] = 0, base[2][0] = 1;
    base[0][1] = 1, base[1][1] = 1, base[2][1] = 1;
    base[0][2] = 1, base[1][2] = 2, base[2][2] = 2;
    pbase[0][0] = 1, pbase[1][0] = 0, pbase[2][0] = 0;
    pbase[0][1] = 1, pbase[1][1] = 1, pbase[2][1] = 0;
    pbase[0][2] = 1, pbase[1][2] = 2, pbase[2][2] = 1;
    ans[0][0] = 1;
    a[0] = -1;
    for (int i = 1; i <= m; i++) ans = ans * (base ^ (a[i] - a[i - 1] - 1)) * pbase;
    ans = ans * (base ^ (n - a[m] - 1));
    cout << ans[0][2] << endl;
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