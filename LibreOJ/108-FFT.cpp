/**
 * @file 108-FFT.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 400005

const double PI = acos(-1);

complex<double> a[maxn], b[maxn];
int rev[maxn];

void DFT(complex<double> a[], int len, int mode) {
    for (int i = 0; i < len; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < len; i <<= 1) {
        complex<double> base(cos(PI / i), mode * sin(PI / i));
        for (int j = 0; j < len; j += i << 1) {
            complex<double> w(1, 0);
            for (int k = j; k < j + i; k++, w *= base)
                tie(a[k], a[k + i]) = make_pair(a[k] + w * a[k + i], a[k] - w * a[k + i]);
        }
    }
    if (mode == -1)
        for (int i = 0; i < len; i++) a[i].real(a[i].real() / len);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0, x; i <= n; i++) cin >> x, a[i].real(x);
    for (int i = 0, x; i <= m; i++) cin >> x, b[i].real(x);
    int len = 1, lgLen = 0;
    while (len <= n + m) len <<= 1, lgLen++;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    DFT(a, len, +1), DFT(b, len, +1);
    for (int i = 0; i < len; i++) a[i] *= b[i];
    DFT(a, len, -1);
    for (int i = 0; i <= n + m; i++) cout << int(a[i].real() + 0.5) << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}