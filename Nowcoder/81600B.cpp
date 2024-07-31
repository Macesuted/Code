/**
 * @file 81600B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool solve(void) {
    int64_t n, m, a, b;
    cin >> n >> m >> a >> b, a = !a, b = !b;
    if (n > m) swap(n, m);

    if (n == 1 && m == 2) return true;
    if (n % 2 == 1 && m % 2 == 1) return false;

    if (a == 1 && b == 1) return false;
    if (a == 0 && b == 0) return true;
    if (a == 1) {
        if (n == 1) return false;
        return true;
    }
    if (b == 1) {
        if (n == 1) return true;
        return false;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "Yes" : "No") << endl;

    return 0;
}