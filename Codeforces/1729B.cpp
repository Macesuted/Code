/**
 * @file 1729B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

void solve(void) {
    string s;
    int n;
    cin >> n >> s, s = " " + s;
    stack<char> S;
    for (int i = n; i; i--) {
        int v = 0;
        if (s[i] == '0')
            v = (s[i - 2] - '0') * 10 + (s[i - 1] - '0'), i -= 2;
        else
            v = s[i] - '0';
        S.push('a' + v - 1);
    }
    while (!S.empty()) cout << S.top(), S.pop();
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