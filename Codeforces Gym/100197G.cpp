/**
 * @file 100197G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

#define maxn 1005

typedef pair<int, int> pii;

int a[maxn], b[maxn];
pii delt[maxn];

void solve(void) {
    int n, S, T, rest;
    cin >> n >> T >> S, rest = T;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i] * T / S, rest -= b[i], delt[i] = {((b[i] + 1) * S - a[i] * T) - (a[i] * T - b[i] * S), i};
    sort(delt + 1, delt + n + 1);
    for (int i = 1; i <= rest; i++) b[delt[i].second]++;
    for (int i = 1; i <= n; i++) cout << b[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
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