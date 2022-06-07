/**
 * @file 12920.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-07
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

#define maxn 100005
#define maxsqrtn 350
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

int a[maxn], buc[maxsqrtn][maxn], L[maxsqrtn], R[maxsqrtn], bel[maxn];
bool vis[maxn];
int64_t fac[maxn], ifac[maxn], inv[maxn], ans[maxsqrtn][maxsqrtn], bbuc[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int B = sqrt(n), bcnt = n / B;
    for (int i = 1; i <= bcnt; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + B;
    if (R[bcnt] < n) bcnt++, L[bcnt] = R[bcnt - 1] + 1, R[bcnt] = n;
    for (int i = 1; i <= bcnt; i++)
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
    for (int i = 1; i <= bcnt; i++) {
        for (int j = 1; j < maxn; j++) buc[i][j] = buc[i - 1][j];
        for (int j = L[i]; j <= R[i]; j++) buc[i][a[j]]++;
    }
    for (int i = 1; i <= bcnt; i++) {
        for (int j = 1; j < maxn; j++) bbuc[j] = 0;
        int64_t tot = 1;
        ans[i][i - 1] = 1;
        for (int j = i; j <= bcnt; j++) {
            for (int k = L[j]; k <= R[j]; k++) bbuc[a[k]]++, tot = tot * inv[bbuc[a[k]]] % mod * (bbuc[a[k]] + 1) % mod;
            ans[i][j] = tot;
        }
    }
    for (int j = 1; j < maxn; j++) bbuc[j] = 0;
    int q, lastans = 0;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l ^= lastans, r ^= lastans;
        int bl = bel[l], br = bel[r];
        int64_t tot = 1;
        if (bl == br) {
            for (int i = l; i <= r; i++) bbuc[a[i]]++, tot = tot * inv[bbuc[a[i]]] % mod * (bbuc[a[i]] + 1) % mod;
            for (int i = l; i <= r; i++) bbuc[a[i]] = 0;
            cout << (lastans = tot) << endl;
            continue;
        }
        tot = ans[bl + 1][br - 1];
        for (int i = l; i <= R[bl]; i++) {
            if (!vis[a[i]]) vis[a[i]] = true, bbuc[a[i]] = buc[br - 1][a[i]] - buc[bl][a[i]];
            bbuc[a[i]]++, tot = tot * inv[bbuc[a[i]]] % mod * (bbuc[a[i]] + 1) % mod;
        }
        for (int i = L[br]; i <= r; i++) {
            if (!vis[a[i]]) vis[a[i]] = true, bbuc[a[i]] = buc[br - 1][a[i]] - buc[bl][a[i]];
            bbuc[a[i]]++, tot = tot * inv[bbuc[a[i]]] % mod * (bbuc[a[i]] + 1) % mod;
        }
        for (int i = l; i <= R[bl]; i++) vis[a[i]] = false, bbuc[a[i]] = 0;
        for (int i = L[br]; i <= r; i++) vis[a[i]] = false, bbuc[a[i]] = 0;
        cout << (lastans = tot) << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("color.in", "r", stdin), freopen("color.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxn; i++) inv[i] = ifac[i] * fac[i - 1] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}