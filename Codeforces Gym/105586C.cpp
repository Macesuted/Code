/**
 * @file 105586C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

#define maxn 100005

typedef pair<int64_t, int64_t> pll;

pll a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    int64_t timL = 0, timR = 1e18;
    for (int i = 1; i <= n; i++) {
        timL++, timR++;
        if (timL < a[i].first) timL = a[i].first;
        if (timR > a[i].second) timR = a[i].second;
        if (timL > timR) return cout << -1 << endl, void();
        if (timR < a[i].second) timR = a[i].second;
    }
    cout << timL + 1 << endl;
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