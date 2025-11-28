/**
 * @file 14948.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool ac[450][20];
int cnt[450];

void solve(void) {
    int n;
    cin >> n;
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (ac[a][b]) {
            cout << 0 << endl;
            continue;
        }

        if (c < 240 || cnt[a] < 3)
            cout << b << endl;
        else
            cout << 0 << endl;

        ac[a][b] = true, cnt[a]++;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
