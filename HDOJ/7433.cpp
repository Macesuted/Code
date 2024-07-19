/**
 * @file 7433.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1050000

const int64_t mod1 = 1000000007, mod2 = 1000000009;
const int64_t val1 = 97, val2 = 79;

int64_t fac1[maxn], fac2[maxn], hash1[maxn], hash2[maxn], hash3[maxn], hash4[maxn];

int64_t getHash(int64_t hash[], int64_t fac[], int64_t mod, int l, int r) {
    return (hash[r] + mod - hash[l - 1] * fac[r - l + 1] % mod) % mod;
}

set<int64_t> cnt;

void solve(void) {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    hash1[0] = hash2[0] = hash3[0] = hash4[0] = 0, cnt.clear(), s = ' ' + s, t = ' ' + t;
    for (int i = 1; i <= n; i++)
        hash1[i] = (hash1[i - 1] * val1 + (s[i] - 'A')) % mod1, hash2[i] = (hash2[i - 1] * val2 + (s[i] - 'A')) % mod2;
    for (int i = 1; i <= m; i++)
        hash3[i] = (hash3[i - 1] * val1 + (t[i] - 'A')) % mod1, hash4[i] = (hash4[i - 1] * val2 + (t[i] - 'A')) % mod2;
    cnt.insert(hash1[n] * mod2 + hash2[n]);
    for (int i = 2; i <= n; i++) {
        int64_t h1 = (getHash(hash1, fac1, mod1, i, n) * fac1[i - 1] + getHash(hash1, fac1, mod1, 1, i - 1)) % mod1,
                h2 = (getHash(hash2, fac2, mod2, i, n) * fac2[i - 1] + getHash(hash2, fac2, mod2, 1, i - 1)) % mod2;
        cnt.insert(h1 * mod2 + h2);
    }
    int ans = 0;
    for (int l = 1, r = n; r <= m; l++, r++) {
        int64_t h1 = getHash(hash3, fac1, mod1, l, r), h2 = getHash(hash4, fac2, mod2, l, r);
        if (cnt.count(h1 * mod2 + h2)) ans++;
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    fac1[0] = fac2[0] = 1;
    for (int i = 1; i < maxn; i++) fac1[i] = fac1[i - 1] * val1 % mod1, fac2[i] = fac2[i - 1] * val2 % mod2;

    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}