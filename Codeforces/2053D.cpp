/**
 * @file 2053D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

void solve(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    vector<int> sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    int64_t ans = 1;
    for (int i = 0; i < n; i++) ans = ans * min(sa[i], sb[i]) % mod;
    cout << ans << ' ';

    while (q--) {
        int o, p;
        cin >> o >> p, p--;
        if (o == 1) {
            int x = lower_bound(sa.begin(), sa.end(), ++a[p]) - sa.begin() - 1;
            ans = ans * inv(min(sa[x], sb[x])) % mod;
            sa[x]++;
            ans = ans * min(sa[x], sb[x]) % mod;
        } else {
            int x = lower_bound(sb.begin(), sb.end(), ++b[p]) - sb.begin() - 1;
            ans = ans * inv(min(sa[x], sb[x])) % mod;
            sb[x]++;
            ans = ans * min(sa[x], sb[x]) % mod;
        }
        cout << ans << ' ';
    }
    cout << endl;

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