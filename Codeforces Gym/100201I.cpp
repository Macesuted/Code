/**
 * @file 100201I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-09
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

int a[1 << 14];

void solve(int d, int l, int r) {
    if (!~d) return;
    stack<int> S;
    int x = l - 1;
    for (int i = l; i <= r; i++) {
        cout << a[i] + 1 << ' ';
        if (a[i] >> d & 1)
            S.push(a[i]);
        else
            cout << a[i] + 1 << ' ', a[++x] = a[i];
    }
    int c = x;
    while (!S.empty()) cout << S.top() + 1 << ' ', a[++x] = S.top(), S.pop();
    return solve(d - 1, l, c), solve(d - 1, c + 1, r);
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 0; i < (1 << n); i++) cin >> a[i], a[i]--;

    solve(n - 1, 0, (1 << n) - 1);
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("railsort.in", "r", stdin), freopen("railsort.out", "w", stdout);
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