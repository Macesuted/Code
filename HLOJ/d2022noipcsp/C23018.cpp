/**
 * @file C23018.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 205
#define mod 1000000007

int a[maxn], f[maxn][maxn * maxn], g[maxn][maxn * maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }
int Add(int &p, int v) { return p = Mod(p + v); }

void solve(void) {
    int n, m, v;
    cin >> n >> m >> v;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int maxS = n * m;
    int ans = 1;
    {
        int L = 1, R = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= maxS; j++) f[i][j] = 0;
        f[0][0] = 1;
        auto incR = [&](void) {
            R++;
            int delt = a[R] - a[R - 1];
            for (int i = n - 1; ~i; i--)
                for (int j = maxS - i * delt; j >= 0; j--)
                    if (f[i][j]) {
                        int v = f[i][j];
                        f[i][j] = 0, Add(f[i + 1][j + i * delt], v), Add(f[i][j + i * delt], v);
                    }
            return;
        };
        auto incL = [&](void) {
            int delt = a[R] - a[L];
            for (int i = 1; i <= n; i++)
                for (int j = delt; j <= maxS; j++) Add(f[i][j], mod - f[i - 1][j - delt]);
            L++;
            return;
        };
        for (int i = 1; i <= n; i++) {
            while (a[i] - a[L] > m) incL();
            if (R < i - 1) incR();
            int delt = a[i] - a[R];
            for (int j = max(0, v - n + i); j <= R - L + 1; j++)
                for (int k = 0; k + j * delt <= m * v; k++) Add(ans, f[j][k]);
        }
    }
    {
        int L = 2, R = 1;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= maxS; j++) f[i][j] = 0;
        f[0][0] = 1;
        auto incR = [&](void) {
            R++;
            int delt = a[L] + m - a[R];
            for (int i = n; i; i--)
                for (int j = delt; j <= maxS; j++) Add(f[i][j], f[i - 1][j - delt]);
            return;
        };
        auto incL = [&](void) {
            int delt = a[L + 1] - a[L];
            for (int i = 1; i <= n; i++)
                for (int j = maxS; ~j; j--) {
                    int v = 0;
                    if (j - i * delt >= 0) v = f[i][j - i * delt];
                    if (j - i * delt - m >= 0) Add(v, mod - f[i - 1][j - delt - m]);
                    f[i][j] = v;
                }
            L++;
            return;
        };
        for (int i = 1; i <= n; i++) {
            while (R < n && a[R + 1] <= a[i] + m) incR();
            if (L == i) incL();
            int delt = a[L] - a[i];
            for (int j = max(0, n - i - v + 2); j <= R - L + 1; j++)
                for (int k = delt * j + m * max(0, v - n + j); k <= maxS; k++) Add(ans, f[j][k]);
        }
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("medium.in", "r", stdin), freopen("medium.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}