/**
 * @file E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxk 100005

int64_t k;
int64_t a[maxk], b[maxk], val[80], kpow[80];

bool chk(int64_t x) {
    int64_t v = x;
    int t = 0;
    while (v) val[t++] = v % k, v /= k;

    kpow[0] = 1;
    for (int i = 1; i < t; i++) kpow[i] = kpow[i - 1] * k;
    for (int i = 0; i < k; i++) b[i] = 0;

    int64_t suf = 1;
    for (int i = 0; i < t; i++) {
        b[val[i]] += suf;

        int64_t vc = 0;
        for (int p = (i == t - 1); p < val[i]; p++) b[p] += kpow[i], vc++;
        if (i < t - 1)
            for (int p = 1; p < k; p++) b[p] += kpow[i], vc++;
        if (i)
            for (int p = 0; p < k; p++) b[p] += i * vc * kpow[i - 1];

        suf += val[i] * kpow[i];
    }

    for (int i = 0; i < k; i++)
        if (a[i] < b[i]) return false;

    return true;
}

void solve(void) {
    cin >> k;
    for (int i = 0; i < k; i++) cin >> a[i];

    int64_t l = 0, r = 2e14;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1;
        (chk(mid) ? l : r) = mid;
    }

    if (l == 0) return cout << -1 << endl, void();

    chk(l);

    for (int i = 0; i < k; i++)
        if (a[i] != b[i]) return cout << -1 << endl, void();

    cout << l << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}