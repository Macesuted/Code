/**
 * @file 108-NTT.cpp
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
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

const int64_t inv3 = Inv(3);

int64_t a[maxn], b[maxn];
int rev[maxn];

void DFT(int64_t a[], int len, int mode) {
    for (int i = 0; i < len; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < len; i <<= 1) {
        int64_t base = Pow(mode == 1 ? 3 : inv3, (mod - 1) / (i << 1));
        for (int j = 0; j < len; j += i << 1) {
            int64_t w = 1;
            for (int k = j; k < j + i; k++, w = w * base % mod)
                tie(a[k], a[k + i]) = make_pair((a[k] + w * a[k + i]) % mod, (a[k] + mod - w * a[k + i] % mod) % mod);
        }
    }
    if (mode == -1) {
        int64_t invLen = Inv(len);
        for (int i = 0; i < len; i++) a[i] = a[i] * invLen % mod;
    }
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];
    int len = 1, lgLen = 0;
    while (len <= n + m) len <<= 1, lgLen++;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    DFT(a, len, +1), DFT(b, len, +1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    DFT(a, len, -1);
    for (int i = 0; i <= n + m; i++) cout << a[i] << ' ';
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