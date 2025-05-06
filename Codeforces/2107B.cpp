/**
 * @file 2107B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 100005

int a[maxn];

void solve(void) {
    int n, k, sum = false;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], sum ^= a[i] & 1;
    if (!(sum & 1)) return cout << "Jerry" << endl, void();
    sort(a + 1, a + n + 1), a[n]--, sort(a + 1, a + n + 1);
    if (a[n] - a[1] > k) return cout << "Jerry" << endl, void();
    cout << "Tom" << endl;
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