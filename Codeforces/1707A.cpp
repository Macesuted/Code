/**
 * @file 1707A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-16
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

#define maxn 100005

int a[maxn];
bool v[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], v[i] = false;
    for (int i = 1, j = n; i <= q && j >= 1; i++) {
        while (j >= 1 && a[j] < i) v[j--] = true;
        if (j >= 1) v[j--] = true;
        if (i == q)
            while (j >= 1) v[j] = (a[j] <= q), j--;
    }
    for (int i = 1; i <= n; i++) cout << v[i];
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