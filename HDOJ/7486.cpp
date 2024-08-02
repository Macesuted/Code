/**
 * @file 7486.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

bool solve(int a, int b, int c) {
    int cnt = a % 2 + b % 2 + c % 2;
    if (cnt == 1 || cnt == 2) return true;
    if (cnt == 3) return false;
    return solve(a / 2, b / 2, c / 2);
}

void solve(void) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << (solve(a, b, c) ? "YES" : "NO") << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}