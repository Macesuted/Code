/**
 * @file 2667.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define mod 1000000007

class Matrix {
   private:
    int64_t a[3][3];

   public:
    Matrix(void) { memset(a, 0, sizeof(a)); }
    void clear(void) { return memset(a, 0, sizeof(a)), void(); }
    int64_t* operator[](size_t x) { return a[x]; }
    int64_t g(size_t x, size_t y) const { return a[x][y]; }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        ans[0][0] = (this->g(0, 0) * o.g(0, 0) + this->g(0, 1) * o.g(1, 0) + this->g(0, 2) * o.g(2, 0)) % mod;
        ans[0][1] = (this->g(0, 0) * o.g(0, 1) + this->g(0, 1) * o.g(1, 1) + this->g(0, 2) * o.g(2, 1)) % mod;
        ans[0][2] = (this->g(0, 0) * o.g(0, 2) + this->g(0, 1) * o.g(1, 2) + this->g(0, 2) * o.g(2, 2)) % mod;
        ans[1][0] = (this->g(1, 0) * o.g(0, 0) + this->g(1, 1) * o.g(1, 0) + this->g(1, 2) * o.g(2, 0)) % mod;
        ans[1][1] = (this->g(1, 0) * o.g(0, 1) + this->g(1, 1) * o.g(1, 1) + this->g(1, 2) * o.g(2, 1)) % mod;
        ans[1][2] = (this->g(1, 0) * o.g(0, 2) + this->g(1, 1) * o.g(1, 2) + this->g(1, 2) * o.g(2, 2)) % mod;
        ans[2][0] = (this->g(2, 0) * o.g(0, 0) + this->g(2, 1) * o.g(1, 0) + this->g(2, 2) * o.g(2, 0)) % mod;
        ans[2][1] = (this->g(2, 0) * o.g(0, 1) + this->g(2, 1) * o.g(1, 1) + this->g(2, 2) * o.g(2, 1)) % mod;
        ans[2][2] = (this->g(2, 0) * o.g(0, 2) + this->g(2, 1) * o.g(1, 2) + this->g(2, 2) * o.g(2, 2)) % mod;
        return ans;
    }
    Matrix operator^(int x) {
        Matrix ans, a = *this;
        ans[0][0] = ans[1][1] = ans[2][2] = 1;
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

void solve(void) {
    string n, m;
    int a, b, c, d;
    cin >> n >> m >> a >> b >> c >> d;
    reverse(n.begin(), n.end()), reverse(m.begin(), m.end());
    auto dec = [](string& s) {
        int p = 0;
        while (s[p] == '0') s[p++] = '9';
        s[p]--;
        while (!s.empty() && !(s.back() ^ 48)) s.pop_back();
        return;
    };
    dec(n), dec(m);
    reverse(n.begin(), n.end()), reverse(m.begin(), m.end());
    Matrix base, A, basep;
    base[0][0] = base[1][1] = a, base[2][1] = b, base[2][2] = 1;
    A[0][0] = 1, A[0][1] = 0, A[0][2] = 1;
    basep[0][0] = basep[1][1] = basep[2][2] = 1;
    for (auto i : m) basep = (basep ^ 10) * (base ^ (i - '0'));
    A = A * basep, a = A[0][0], b = A[0][1];
    A.clear(), base.clear(), basep.clear();
    base[0][0] = 1LL * a * c % mod, base[1][0] = (1LL * b * c + d) % mod, base[1][1] = 1;
    A[0][0] = A[0][1] = 1;
    basep[0][0] = basep[1][1] = basep[2][2] = 1;
    for (auto i : n) basep = (basep ^ 10) * (base ^ (i - '0'));
    cout << ((A * basep)[0][0] * a + b) % mod << endl;
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