/**
 * @file 1245.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 2005

typedef tuple<int, int, int> tiii;

int f[maxn][maxn], g[maxn][maxn];
tiii a[maxn];

void solve(void) {
    int n, A, B;
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) cin >> get<2>(a[i]) >> get<1>(a[i]) >> get<0>(a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= B; j++) f[i][j] = f[i - 1][j];
        int v = get<0>(a[i]) * get<1>(a[i]);
        for (int j = v; j <= B; j++) f[i][j] = max(f[i - 1][j], f[i - 1][j - v] + get<2>(a[i]));
    }
    for (int i = n; i; i--) {
        for (int j = 0; j <= A; j++) g[i][j] = g[i + 1][j];
        for (int j = get<1>(a[i]); j <= A; j++) g[i][j] = max(g[i + 1][j], g[i + 1][j - get<1>(a[i])] + get<2>(a[i]));
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= get<1>(a[i]); j++) {
            int v = get<0>(a[i]) * j;
            if (get<1>(a[i]) - j <= A && v <= B)
                ans = max(ans, f[i - 1][B - v] + get<2>(a[i]) + g[i + 1][A - get<1>(a[i]) + j]);
        }
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}