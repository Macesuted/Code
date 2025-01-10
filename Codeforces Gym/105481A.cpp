/**
 * @file 105481A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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

set<string> S;

void solve(void) {
    string text;
    getline(cin, text);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        S.insert(s);
    }
    stringstream ssin(text);
    string s;
    int ans = 0;
    while (ssin >> s) {
        while (!s.empty() && (s.back() == '.' || s.back() == ',' || s.back() == '!' || s.back() == '?')) s.pop_back();
        for (auto &c : s)
            if ('A' <= c && c <= 'Z') c = c - 'A' + 'a';
        if (S.count(s)) continue;
        ans++, S.insert(s);
    }
    cout << ans << endl;
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