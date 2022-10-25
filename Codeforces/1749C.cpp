/**
 * @file 1749C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-20
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

#define maxn 105

int n, a[maxn];

bool check(int k) {
    for (int i = 1, l = 0, r = n; i <= k; i++) {
        while (l < r && a[r] > k - i + 1) r--;
        if (l >= r) return false;
        l++, r--;
    }
    return true;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int k = 0;
    for (int i = 1; i <= n; i++)
        if (check(i)) k = max(k, i);
    cout << k << endl;
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