/**
 * @file 7444.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 2005
#define mod 998244353

typedef pair<int, int> pii;

multiset<pii> S;
map<int, vector<pii>> rec;

int64_t s[maxn], fac[maxn], ifac[maxn], C[maxn][maxn], invC[maxn][maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    int n;
    cin >> n;
    for (int i = 1, xl, xr, yl, yr; i <= n; i++) {
        cin >> xl >> yl >> xr >> yr;
        rec[xl].emplace_back(yl, yr), rec[xr].emplace_back(-yl, -yr);
    }
    int lastx = 0;
    for (auto &[x, vec] : rec) {
        {
            int lasty = 0, v = 0;
            for (auto [y, delt] : S) {
                s[v] = (s[v] + int64_t(y - lasty) * (x - lastx)) % mod;
                v += delt, lasty = y;
            }
        }
        for (auto [l, r] : vec)
            if (l > 0)
                S.emplace(l, +1), S.emplace(r, -1);
            else
                S.erase(S.find({-l, +1})), S.erase(S.find({-r, -1}));
        lastx = x;
    }
    for (int k = 1; k <= n; k++) {
        int64_t ans = 0, tot = inv(C[n][k]);
        for (int i = 1; i <= n; i++)
            if (n - i < k)
                ans = (ans + s[i]) % mod;
            else
                ans = (ans + s[i] * (mod + 1 - C[n - i][k] * tot % mod)) % mod;
        cout << ans << endl;
    }
    return 0;
}