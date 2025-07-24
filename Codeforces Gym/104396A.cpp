/**
 * @file 104396A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
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

void solve(void) {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    int rest = 1;
    for (int i = 0; i < 100; i++) rest = rest * 10 % 26;

    while (m > (int)s.size() / 2) {
        string tl = s.substr(0, s.size() / 2), tc = s, tr = s.substr(s.size() / 2);
        for (char& c : tr) c = (c - 'a' + 1) % 26 + 'a';
        s = tl + tc + tr, rest = (rest + 25) % 26;
    }
    for (size_t i = s.size() - m; i < s.size(); i++) cout << char((s[i] - 'a' + rest) % 26 + 'a');
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}