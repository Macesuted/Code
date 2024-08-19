/**
 * @file 7549.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

int64_t base1 = 131, mod1 = 1e9 + 7, base2 = 1331, mod2 = 1e9 + 9;

int64_t hA[maxn], hB[maxn], gA[maxn], gB[maxn], powh[maxn], powg[maxn];

int64_t getHash(int64_t v[], int64_t p[], int64_t mod, int l, int r) {
    return (v[r] + mod - v[l - 1] * p[r - l + 1] % mod) % mod;
}

int solve(string A, string B) {
    hA[0] = hB[0] = gA[0] = gB[0] = 0;
    int n = A.size(), m = B.size();
    for (int i = 1; i <= n; i++) hA[i] = (hA[i - 1] * base1 + A[i - 1]) % mod1, gA[i] = (gA[i - 1] * base2 + A[i - 1]) % mod2;
    for (int i = 1; i <= m; i++) hB[i] = (hB[i - 1] * base1 + B[i - 1]) % mod1, gB[i] = (gB[i - 1] * base2 + B[i - 1]) % mod2;
    int cnt = 0, l = 1, r = n;
    for (; r <= m; l++, r++)
        cnt += (getHash(hA, powh, mod1, 1, n) == getHash(hB, powh, mod1, l, r) &&
                getHash(gA, powg, mod2, 1, n) == getHash(gB, powg, mod2, l, r));
    if (cnt > 1) return INT_MAX;
    if (cnt == 1) return m;
    for (; l <= m; l++, r++)
        if (getHash(hA, powh, mod1, 1, m - l + 1) == getHash(hB, powh, mod1, l, m) &&
            getHash(gA, powg, mod2, 1, m - l + 1) == getHash(gB, powg, mod2, l, m))
            return r;
    return n + m;
}

void solve(void) {
    string A, B;
    cin >> A >> B;
    int ans1 = solve(A, B), ans2 = solve(B, A);
    if (max(ans1, ans2) == INT_MAX) return cout << -1 << endl, void();
    cout << min(ans1, ans2) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    powh[0] = powg[0] = 1;
    for (int i = 1; i < maxn; i++) powh[i] = powh[i - 1] * base1 % mod1, powg[i] = powg[i - 1] * base2 % mod2;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}