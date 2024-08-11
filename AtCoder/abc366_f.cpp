/**
 * @file abc366_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

pii a[maxn];
int64_t f[maxn][15];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1, [&](pii x, pii y) { return (x.first - 1.) / x.second < (y.first - 1.) / y.second; });
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            f[i][j] = f[i - 1][j];
            if (j) f[i][j] = max(f[i][j], f[i - 1][j - 1] * a[i].first + a[i].second);
        }
    cout << f[n][k] << endl;
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