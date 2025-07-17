/**
 * @file 100431D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

#define maxn 205

int x[maxn];
vector<int> a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
        for (int j = 1, x; j <= i; j++) cin >> x, a[i].push_back(x);
    for (int i = 1; i <= n; i++) x[i] = i;
    for (int v = n - 1; v >= 1; v--)
        for (int i = v; i < n; i += 2) {
            if (x[i] > x[i + 1]) return cout << "NO" << endl, void();
            if (a[i].back()) swap(x[i], x[i + 1]);
            a[i].pop_back();
        }
    for (int v = 2; v < n; v++)
        for (int i = v; i < n; i += 2) {
            if (x[i] > x[i + 1]) return cout << "NO" << endl, void();
            if (a[i].back()) swap(x[i], x[i + 1]);
            a[i].pop_back();
        }
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) cout << x[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("bubble.in", "r", stdin), freopen("bubble.out", "w", stdout);
#endif
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