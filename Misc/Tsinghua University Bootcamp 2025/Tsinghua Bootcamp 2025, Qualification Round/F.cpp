/**
 * @file F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-06-29
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

map<int, int> rec;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++) cin >> x, rec[x]++;

    if (rec[0] == n) return cout << 0 << endl, void();

    int ans = 0;
    while (rec[ans]) ans++;

    if (ans == n) return cout << n - 1 << endl, void();

    cout << ans + 1 << endl;

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

/*
5
0 1 2 3 4

4 0 1 2 3
0 1 2 3 5
ans = 4

*/