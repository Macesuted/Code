/**
 * @file 5523.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int to[1 << 24], f[1 << 24];

void solve(void) {
    int n;
    cin >> n;
    int U = (1 << n) - 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c, to[1 << i] |= (c == '1') << j;
        }
    for (int S = 0; S <= U; S++)
        for (int i = 0; i < n; i++)
            if (S >> i & 1) to[S] |= to[1 << i];
    f[1] = 1;
    for (int S = 1; S <= U; S += 2)
        for (int i = 0; i < n; i++)
            if (!(S >> i & 1) && (to[f[S]] >> i & 1)) f[S | (1 << i)] |= 1 << i;
    auto print = [&](int v) {
        for (int i = 0; i < n; i++) cout << (v >> i & 1);
        cout << endl;
    };
    print(f[U]);
    for (int i = 1; i < n; i++) {
        int T = 0;
        for (int S = 1; S <= U; S += 2)
            if (f[S] >> i & 1) T |= f[(U ^ S) | 1];
        print(T);
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}