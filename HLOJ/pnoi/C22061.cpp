/**
 * @file C22061.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-08
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

string s;
vector<int> rec;

void solve(void) {
    int n;
    cin >> n >> s, s = " " + s;
    for (int i = 1, l = 1; i <= n + 1; i++)
        if (i > n || s[i] != s[l]) rec.push_back(i - l), l = i;
    int ans = 0;
    for (int i = 0; i < (int)rec.size(); i++) {
        ans = max(ans, rec[i]);
        if (i + 2 < (int)rec.size()) ans = max(ans, rec[i] + rec[i + 2]);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
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