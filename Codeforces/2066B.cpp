/**
 * @file 2066B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-11
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

#define maxn 200005

int a[maxn], b[maxn], mv[maxn];

void solve(void) {
    int n;
    cin >> n;
    int cnt0 = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt0 += (a[i] == 0);

    if (!cnt0) return cout << n << endl, void();

    bool met = false;
    int m = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] || !met) b[++m] = a[i], met |= (a[i] == 0);

    bool chk = true;
    unordered_set<int> S;
    mv[0] = INT_MAX;
    for (int i = 1; i <= m; i++) mv[i] = min(mv[i - 1], b[i]);
    for (int i = m, mex = 0; i > 1 && chk; i--) {
        S.insert(b[i]);
        while (S.count(mex)) mex++;
        if (mv[i - 1] < mex) chk = false;
    }

    cout << (chk ? m : m - 1) << endl;

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