/**
 * @file 9136.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
void solve(void) {
    int n = 4, k = 2048;
    cout << 25 << endl;
    cout << "$0 = $1 * " << fixed << 1. / k << endl;
    for (int i = 1; i <= n; i++) cout << "$" << i << " = $0 * $" << i - 1 << endl;
    for (int i = 1; i <= n; i++) {
        double frac = 1;
        for (int j = 1; j <= i + 1; j++) frac /= j;
        cout << "$" << i << " = $" << i << " * " << fixed << frac << endl;
    }
    cout << "$0 = $0 + 1" << endl;
    for (int i = 1; i <= n; i++) cout << "$0 = $0 + $" << i << endl;
    for (int i = 2; i <= k; i *= 2) cout << "$0 = $0 * $0" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cout << setprecision(15);
    solve();

    return 0;
}
