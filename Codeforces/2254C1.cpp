/**
 * @file 2254C1.cpp
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
    string s[2];
    cin >> n >> s[0] >> s[1];

    vector<int> cnt[2][2];
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < n; i++)
            if (s[t][i] == '1') cnt[t][i & 1].push_back(i);

    cout << ((cnt[0][0].size() != cnt[1][0].size() || cnt[0][1].size() != cnt[1][1].size()) ? "NO" : "YES") << endl;

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
