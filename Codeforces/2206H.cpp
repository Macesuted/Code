/**
 * @file 2206H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int64_t> rec;
    for (int i = 1; i < n; i++)
        if (a[i] != a[i + 1]) rec.push_back(2 * abs(a[i] - a[i + 1]));

    if (rec.empty()) return cout << a[n] << endl, void();

    int64_t delt = rec.front();
    for (auto v : rec) delt = gcd(delt, v);

    int64_t p = a[1] % delt;
    if (p == 0) p = delt;

    for (int i = 1; i < n; i++) p += abs(a[i] - a[i + 1]);

    cout << p << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}