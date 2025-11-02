/**
 * @file 14687.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto calc = [&](void) -> int {
        int v = 0;
        for (int i = 1; i <= n; i++) v += (v >= a[i] ? +1 : -1);
        return v;
    };

    sort(a + 1, a + n + 1);
    cout << calc() << ' ';
    reverse(a + 1, a + n + 1);
    cout << calc() << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}