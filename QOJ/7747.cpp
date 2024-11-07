/**
 * @file 7747.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n;
    cin >> n;
    bool rest = false;
    int v = 0;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (v % 2) v--, rest = true;
        v = v / 2 + x;
        if (v == 0 && !rest)
            cout << '0';
        else
            cout << "-+"[v >= 0];
    }
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}