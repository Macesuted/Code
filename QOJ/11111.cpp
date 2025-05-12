/**
 * @file 11111.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005
#define mod 1'000'000'007

int64_t a[maxn], add[maxn], mul[maxn];
int64_t f[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t x = 1;
    for (int i = 1; i <= n; i++) cin >> a[i], x = min((__int128_t)1e18, (__int128_t)x * a[i]);
    if (x == 1e18) {
        int l = 1, r = n;
        int64_t ans = 0;
        while (a[l] == 1) l++, ans++;
        while (a[r] == 1) r--, ans++;
        int64_t mul = 1;
        for (int i = l; i <= r; i++) mul = mul * a[i] % mod;
        cout << (ans + mul) % mod << endl;
        return;
    }
    int m = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        if (a[l] > 1) {
            m++;
            add[m] = mul[m] = a[l];
            continue;
        }
        while (r + 1 <= n && a[r + 1] == 1) r++;
        m++;
        add[m] = r - l + 1, mul[m] = 1;
    }
    f[0] = 0;
    for (int i = 1; i <= m; i++) {
        int64_t curMul = mul[i], curAdd = add[i];
        f[i] = 0;
        for (int j = i - 1; j >= 0; j--) {
            f[i] = max(f[i], f[j] + max(curMul, curAdd));
            curMul *= mul[j], curAdd += add[j];
        }
    }
    cout << f[m] % mod << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}