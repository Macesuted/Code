/**
 * @file D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-06
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

int a[maxn], b[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    int x = b[k], tot = 0;
    for (int i = 1; i <= n; i++) tot += (a[i] <= x);
    for (int l = 1, r = n; l <= r && tot >= k - 1;) {
        while (l <= r && a[l] > x) l++;
        while (l <= r && a[r] > x) r--;
        if (l >= r) break;
        if (a[l] == a[r]) {
            l++, r--;
            continue;
        }
        if (a[l] == x) {
            l++, tot--;
            continue;
        }
        if (a[r] == x) {
            r--, tot--;
            continue;
        }
        return cout << "NO" << endl, void();
    }
    if (tot < k - 1) return cout << "NO" << endl, void();
    cout << "YES" << endl;
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