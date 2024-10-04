/**
 * @file 9351.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-29
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

#define maxlgn 60

typedef __int128_t int128_t;

int128_t base1, base2, base[maxlgn];
int64_t wgt[maxlgn];

int128_t xor3(int128_t a, int128_t b) {
    return a + b - 3 * (((a & b & base2) >> 1) | ((((a | b) & base2) >> 1) & ((a | b) & base1)));
}

void solve(void) {
    int n;
    cin >> n;

    int64_t ans = 0;
    for (int i = 0; i < maxlgn; i++) base[i] = wgt[i] = 0;
    for (int i = 1; i <= n; i++) {
        int64_t x, y;
        cin >> x >> y, x ^= ans, y ^= ans;

        int128_t v = 0;
        for (int i = 0; i < maxlgn; i++) v |= int128_t(x >> i & 1) << (2 * i);
        for (int i = 0; i < maxlgn; i++) {
            if (!(v >> (2 * i) & 3)) continue;
            if (!base[i]) {
                base[i] = v, ans += wgt[i] = y;
                break;
            }
            if (wgt[i] < y) ans += y - wgt[i], swap(base[i], v), swap(wgt[i], y);
            while (v >> (2 * i) & 3) v = xor3(v, base[i]);
        }

        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxlgn; i++) base1 |= (int128_t)1 << (i * 2), base2 |= (int128_t)2 << (i * 2);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}