/**
 * @file FDUPC25P-A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-27
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

const string way = "ESWN";

void solve(void) {
    char c;
    int q;
    cin >> c >> q;

    int x = 0;
    while (way[x] != c) x++;

    while (q--) {
        cin >> c;
        if (c == 'L') x = (x + 3) & 3;
        if (c == 'R') x = (x + 1) & 3;
        if (c == 'B') x = (x + 2) & 3;
        cout << way[x] << ' ';
    }

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
