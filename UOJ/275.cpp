/**
 * @file 275.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxlgn 65
#define mod 1000000007

typedef __int128_t int128_t;

int K, ns[maxlgn], ms[maxlgn], f[maxlgn][2][2][2][2];
int64_t n, m;
int128_t pwk[maxlgn];

int dp(int p, bool igj, bool li, bool lj, bool sam) {
    if (p == -1) return igj;
    auto& thi = f[p][igj][li][lj][sam];
    if (~thi) return thi;
    thi = 0;
    for (int x = 0; x <= (li ? ns[p] : K - 1); x++)
        for (int y = 0; y <= min(lj ? ms[p] : K - 1, sam ? x : K - 1); y++)
            thi = (thi + dp(p - 1, igj || x < y, li && x == ns[p], lj && y == ms[p], sam && x == y)) % mod;
    return thi;
}

void solve(void) {
    cin >> n >> m, memset(f, -1, sizeof(f)), memset(ns, 0, sizeof(ns)), memset(ms, 0, sizeof(ms));
    int lgn = 0, lgm = 0;
    while (pwk[lgn] <= n) ns[lgn] = n / pwk[lgn] % K, lgn++;
    while (pwk[lgm] <= m) ms[lgm] = m / pwk[lgm] % K, lgm++;
    cout << dp(max(lgn, lgm) - 1, false, true, true, true) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _;
    cin >> _ >> K;
    pwk[0] = 1;
    for (int i = 1; i < maxlgn; i++) pwk[i] = pwk[i - 1] * K;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}