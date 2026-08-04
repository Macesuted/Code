/**
 * @file 2254E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-08-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n;
    cin >> n;

    multiset<int64_t> S;
    for (int i = 1, x; i <= n; i++) cin >> x, S.insert(x);

    vector<int64_t> ans;

    int64_t v = 0;
    for (int i = 1; i <= n; i++) {
        auto p = S.upper_bound(-v);
        if (p == S.end()) return cout << -1 << endl, void();
        ans.push_back(v += *p);
        S.erase(S.find(*p));
    }

    for (auto v : ans) cout << v << ' ';
    cout << endl;

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
