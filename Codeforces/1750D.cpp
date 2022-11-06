/**
 * @file 1750D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
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
#define mod 998244353

int a[maxn];
int64_t f[maxn];
vector<int> num;

void split(int v) {
    num.clear();
    for (int i = 1; i * i <= v; i++) {
        if (v % i) continue;
        num.push_back(i);
        if (i * i < v) num.push_back(v / i);
    }
    sort(num.begin(), num.end());
    return;
}
int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = 1;
    for (int t = 2; t <= n; t++)
        if (a[t] == a[t - 1])
            ans = ans * (m / a[t]) % mod;
        else {
            if (a[t - 1] % a[t]) return cout << 0 << endl, void();
            int v = a[t - 1] / a[t];
            split(v);
            for (int i = 0; i < (int)num.size(); i++) f[i] = 0;
            f[0] = 1;
            int64_t tot = 0;
            for (int i = 0; i < (int)num.size(); i++) {
                tot = (tot + m / a[t] / num[i] % mod * f[i]) % mod;
                for (int j = i + 1; j < (int)num.size(); j++)
                    if (num[j] % num[i] == 0) f[j] = Mod(f[j] + mod - f[i]);
            }
            ans = ans * tot % mod;
        }
    cout << ans << endl;
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