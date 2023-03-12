/**
 * @file C23027.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005
#define mod 998244353

int a[maxn], sum[maxn];
int64_t fac[maxn], ifac[maxn];
bool vis[maxn];
map<int, int> rec;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n;
    cin >> n, rec.clear();
    for (int i = 1; i <= n; i++) cin >> a[i], vis[i] = false, sum[i] = 0;
    for (int i = 1, p, c; i <= n; i++)
        if (!vis[i]) {
            p = i, c = 0;
            while (!vis[p]) vis[p] = true, c++, p = a[p];
            rec[c]++, sum[c] += c;
        }
    int64_t ans = 1;
    if (rec.count(1))
        ans = (rec[1] == 1 ? 1 : Pow(rec[1], rec[1] - 2)), rec.erase(1);
    else if (rec.count(2))
        ans = (rec[2] == 1 ? 1 : Pow(rec[2] * 2 % mod, rec[2] - 1)), rec.erase(2);
    else
        return cout << 0 << endl, void();
    for (auto i : rec) {
        int v = i.first, l = i.second, pre = 0;
        for (int j = 1; j * j <= v; j++)
            if (v % j == 0) {
                pre += sum[j];
                if (j != 1 && v / j != j) pre += sum[v / j];
            }
        int64_t tot = 0;
        for (int i = 1; i <= l; i++)
            tot = (tot + C(l, i) * Pow(pre, i) % mod * Pow(v, l - i) % mod * (i == l ? 1 : i * Pow(l, l - i - 1) % mod)) % mod;
        ans = ans * tot % mod;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("camphor.in", "r", stdin), freopen("camphor.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}