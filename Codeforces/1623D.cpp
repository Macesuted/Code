/**
 * @file 1623D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 100005
#define mod 1000000007

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

bool vis[2 * maxn];

void solve(void) {
    int n, m, rb, cb, rd, cd;
    long long p, rp;
    cin >> n >> m >> rb >> cb >> rd >> cd >> p;
    p = p * Pow(100, mod - 2) % mod, rp = (mod + 1 - p) % mod;
    int t = (2 * n - 2) * (2 * m - 2) / gcd(2 * n - 2, 2 * m - 2);
    for (int i = 0; i < t; i++) vis[i] = false;
    for (int i = 0, tx = rb, ty = cb, rc = 1, cc = 1; i < t; i++) {
        if (tx == rd || ty == cd) vis[i] = true;
        if (tx + rc < 1 || tx + rc > n) rc = -rc;
        if (ty + cc < 1 || ty + cc > m) cc = -cc;
        tx += rc, ty += cc;
    }
    long long ans = 0, frp = 1;
    for (int i = 0; i < t; i++)
        if (vis[i]) ans = (ans + frp * p % mod * i) % mod, frp = frp * rp % mod;
    cout << (ans + t * frp) % mod * Pow((mod + 1 - frp) % mod, mod - 2) % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
