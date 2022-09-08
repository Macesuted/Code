/**
 * @file 1718A1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-08
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

#define maxn 100005

set<int> S;

void solve(void) {
    int n;
    cin >> n, S.insert(0);
    int ans = n;
    for (int i = 1, s = 0, a; i <= n; i++) {
        cin >> a, s ^= a;
        if (S.count(s)) ans--, S.clear();
        S.insert(s);
    }
    cout << ans << endl;
    S.clear();
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