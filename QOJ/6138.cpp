/**
 * @file 6138.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int x, k;
    cin >> x >> k;
    while (x >= 2 && k) {
        int v = x, sum = 0;
        while (v) {
            int t = v % 10;
            v /= 10;
            if (t == 8)
                sum += 2;
            else if (t == 0 || t == 4 || t == 6 || t == 9)
                sum++;
        }
        x = sum, k--;
    }
    if (k) x ^= k & 1;
    cout << x << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}