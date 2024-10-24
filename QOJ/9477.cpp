/**
 * @file 9477.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define mod 998244353

typedef pair<int, int> pii;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = qpow(2, (int64_t)n * (n - 1) / 2 % (mod - 1));
    stack<pii> S;
    S.emplace(n + 1, 0);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        while (S.top().first < x) S.pop();
        if (S.top().second) {
            int64_t v = qpow(2, i - S.top().second);
            ans = ans * (v + mod - 1) % mod * qpow(v, mod - 2) % mod;
        }
        S.emplace(x, i);
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
