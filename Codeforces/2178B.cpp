/**
 * @file 2178B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-27
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
    string s;
    cin >> s;

    int f[2] = {int(1e9), s[0] == 'u'};

    for (auto c : s.substr(1)) {
        if (c == 's')
            f[1] = min(f[0], f[1]), f[0] = 1e9;
        else
            tie(f[0], f[1]) = make_pair(f[1], 1 + min(f[0], f[1]));
    }

    cout << f[1] << endl;

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
