/**
 * @file 5462.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int l, r, b, k;
    cin >> l >> r >> b >> k;
    int64_t range = (l / b + (l % b > 0)) * b;
    cout << k * range << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
