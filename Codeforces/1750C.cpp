/**
 * @file 1750C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
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

typedef pair<int, int> pii;

vector<pii> ans;

void solve(void) {
    int n;
    string s, t;
    cin >> n >> s >> t, s = " " + s, t = " " + t;
    if (s != t) {
        bool chk = true;
        for (int i = 1; i <= n; i++) chk &= (s[i] != t[i]);
        if (!chk) return cout << "NO" << endl, void();
    }
    cout << "YES" << endl;
    ans.clear();
    for (int i = 1; i <= n; i++)
        if (s[i] == '1') ans.emplace_back(i, i);
    if ((ans.size() & 1) == (s == t)) ans.emplace_back(1, 1), ans.emplace_back(2, n), ans.emplace_back(1, n);
    cout << ans.size() << endl;
    for (auto i : ans) cout << i.first << ' ' << i.second << endl;
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