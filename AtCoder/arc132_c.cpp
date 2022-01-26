/**
 * @file arc132_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 505
#define mod 998244353

int a[maxn];
bool force[maxn];
long long f[maxn][1 << 11];

void Plus(long long& a, long long b) { return a = (a + b >= mod ? a + b - mod : a + b), void(); }

void solve(void) {
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i]) force[a[i]] = true;
    }
    f[0][0] = 1;
    int maxS = 1 << (2 * d + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < maxS; j++) {
            if (!f[i][j]) continue;
            if (a[i + 1] != -1) {
                Plus(f[i + 1][(j >> 1) | (1 << (a[i + 1] - (i + 1) + d))], f[i][j]);
                continue;
            }
            for (int t = -d; t <= d; t++) {
                if ((j >> (t + d + 1) & 1) || i + 1 + t < 1 || i + 1 + t > n || force[i + 1 + t]) continue;
                Plus(f[i + 1][(j >> 1) | (1 << (t + d))], f[i][j]);
            }
        }
    cout << f[n][(1 << (d + 1)) - 1] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
