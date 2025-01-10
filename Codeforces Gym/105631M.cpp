/**
 * @file 105631M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
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

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 2, v = 1; i <= n; i += 2, v++) a[i] = v;
    for (int i = n - !(n & 1), c = n / 2 + 1, coef = 1; i >= 1; i -= 2, c = c + coef * (i + 1) / 2, coef = -coef) a[i] = c;
    cout << "Yes" << endl;
    if (n == 4) return cout << "4 1 3 2" << endl, void();
    if (n & 1) {
        swap(a[1], a[2]);
        swap(a[n - 1], a[n]);
    } else {
        swap(a[1], a[2]);
        swap(a[n - 2], a[n - 1]);
    }

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
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