/**
 * @file 7491.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define mod 998244353

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve(void) {
    int n;
    cin >> n;
    cout << qpow(2, n - (n % 3 == 2)) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}