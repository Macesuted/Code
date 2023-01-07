/**
 * @file 247576.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
#include <string>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t, s = " " + s, t = " " + t;
    string os = " ";
    for (int i = 1; i <= n; i++)
        if ('a' <= s[i] && s[i] <= 'z') os.push_back(s[i]);
    for (int i = 1; i < (int)os.size(); i++) {
        bool chk = true;
        for (int j = 1; j <= m; j++) chk &= (os[i + j - 1] == t[j]);
        if (chk) return cout << "YES" << endl, void();
    }
    cout << "NO" << endl;
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