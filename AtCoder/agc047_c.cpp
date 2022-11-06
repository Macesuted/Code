/**
 * @file agc047_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005
#define mod 200003

typedef complex<double> Complex;

const double PI = acos(-1);

Complex a[maxn << 2];
int cnt[maxn], rev[maxn << 2];

void DFT(Complex a[], int n, int mode) {
    for (int i = 0; i < n; i++)
        if (rev[i] > i) swap(a[i], a[rev[i]]);
    for (int i = 1; i < n; i <<= 1) {
        Complex base(cos(PI / i), mode * sin(PI / i));
        for (int j = 0; j < n; j += i << 1) {
            Complex w(1, 0);
            for (int k = j; k < j + i; k++, w *= base)
                tie(a[k], a[k + i]) = make_pair(a[k] + w * a[k + i], a[k] - w * a[k + i]);
        }
    }
    if (mode == -1)
        for (int i = 0; i < n; i++) a[i].real(a[i].real() / n);
    return;
}

void solve(void) {
    int n;
    int64_t ans = 0;
    cin >> n;
    for (int i = 1, v; i <= n; i++) cin >> v, v ? a[cnt[v]].real(a[cnt[v]].real() + 1) : void(), ans -= int64_t(v) * v % mod;
    int len = 1, lgLen = 0;
    while (len <= 2 * mod) len <<= 1, lgLen++;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    DFT(a, len, +1);
    for (int i = 0; i < len; i++) a[i] *= a[i];
    DFT(a, len, -1);
    for (int i = 0, v = 1; i <= 2 * mod - 2; i++, v = v * 2 % mod) ans += int64_t(a[i].real() + 0.5) * v;
    cout << ans / 2 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 1, c = 0; !cnt[i]; i = i * 2 % mod, c++) cnt[i] = c;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}