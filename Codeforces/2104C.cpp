/**
 * @file 2104C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-28
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
    int n;
    string s;
    cin >> n >> s, s = ' ' + s;
    if (s[n] == 'A') {
        if (s[1] == 'A' || s[n - 1] == 'A')
            cout << "Alice" << endl;
        else
            cout << "Bob" << endl;
    } else {
        for (int i = 1; i < n; i++)
            if (s[i] == 'B') return cout << "Bob" << endl, void();
        cout << "Alice" << endl;
    }
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