/**
 * @file 201.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-21
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

bool graph[21][21];

void solve(void) {
    int v;
    cin >> v;
    for (int i = 20; i > 2; i--) graph[i][i - 1] = true;
    for (int i = 2; i < 20; i++)
        for (int j = i + 1; j <= 20; j++) graph[i][j] = true;
    for (int i = 18; i > 1; i--)
        if (v >> (18 - i) & 1) graph[1][i] = true;
    cout << 20 << endl;
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) cout << graph[i][j];
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("constr.in", "r", stdin), freopen("constr.out", "w", stdout);
#endif
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