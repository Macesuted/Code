/**
 * @file 104772J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int a[maxn], b[maxn], f[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int fl = 0, fr = 0;
    for (int i = 1; i <= n; i++) {
        if (b[n] <= a[i]) {
            fl = max(fl, n - i + 1);
            break;
        }
        fl = max(fl, (int)(upper_bound(b + i, b + n + 1, a[i]) - b) - i);
    }
    for (int i = n; i; i--) {
        if (b[1] >= a[i]) {
            fr = max(fr, i);
            break;
        }
        fr = max(fr, i - ((int)(lower_bound(b + 1, b + i + 1, a[i]) - b) - 1));
    }
    fr = n - fr;
    cout << fr - fl + 1 << endl;
    for (int i = fl; i <= fr; i++) cout << i << ' ';
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