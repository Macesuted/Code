/**
 * @file F1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 5005
#define mod 998244353

int64_t f[maxn][maxn];
int nxt[maxn][maxn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }
void Add(int64_t &a, int64_t x) { return a = Mod(a + x), void(); }

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) nxt[i][j] = n + 1;
    for (int i = 1, p, x; i <= m; i++) cin >> p >> x, nxt[p][x] = p;
    for (int i = n - 1; i; i--)
        for (int j = 1; j <= n; j++) nxt[i][j] = min(nxt[i][j], nxt[i + 1][j % n + 1]);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) f[i][j] = 0;

    f[0][0] = 1;

    for (int i = 0; i < n; i++) {
        int64_t sum = 0;
        for (int x = 0; x <= n; x++) Add(sum, f[i][x]);
        for (int s = 1; i + s <= n; s++)
            for (int r = 1; r <= s; r++)
                if (nxt[i + 1][r] > i + s - r + 1 && (r == 1 || nxt[i + s - r + 2][1] > i + s))
                    Add(f[i + s][(r == 1 ? s : 0)], sum);

        for (int x = 1; x <= n; x++) {
            if (!f[i][x]) continue;
            for (int s = x + 1, r = x + 1; i + s <= n; s++)
                if (nxt[i + 1][r] > i + s - r + 1 && (r == 1 || nxt[i + s - r + 2][1] > i + s)) Add(f[i + s][0], mod - f[i][x]);
        }
    }

    int64_t ans = 0;
    for (int i = 0; i <= n; i++) Add(ans, f[n][i]);
    cout << ans << endl;

    return;
}

bool mem2;

int main() {
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