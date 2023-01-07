/**
 * @file 247577.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
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

set<int> S;

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i <= n; i++) S.insert(i);
    while (k--) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            S.erase(x);
        else
            cout << *--S.find(x) << endl;
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