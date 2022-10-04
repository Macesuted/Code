/**
 * @file 1738B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-30
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

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> a[i];
    for (int i = 2; i < k; i++)
        if (a[i] - a[i - 1] > a[i + 1] - a[i]) return cout << "No" << endl, void();
    if (k > 1 && int64_t(a[2] - a[1]) * (n - k + 1) < a[1]) return cout << "No" << endl, void();
    cout << "Yes" << endl;
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