/**
 * @file 105481D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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

typedef pair<int, int> pii;

pii a[maxn];
double f[maxn], g[maxn][maxn];

double dis(int x, int y) {
    return sqrt((int64_t)(a[x].first - a[y].first) * (a[x].first - a[y].first) +
                (int64_t)(a[x].second - a[y].second) * (a[x].second - a[y].second));
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;

    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
        double mv = 0;
        for (int j = i - 1; j; j--) {
            mv = max(mv, dis(i, j));
            g[j][i] = max(g[j][i - 1], mv);
        }
    }

    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) f[i] = max(f[i], f[j - 1] + g[j][i]);
    cout << fixed << setprecision(9) << f[n] << endl;

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