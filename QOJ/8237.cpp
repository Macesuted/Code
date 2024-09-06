/**
 * @file 8237.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005
#define mod 1000000007

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

const int inv2 = inv(2);

int a[maxn], w[maxn], fa[maxn], indeg[maxn];
int64_t f[maxn], fac[maxn], ifac[maxn];
vector<int> graph[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], graph[i].clear(), f[i] = indeg[i] = 0;
    for (int i = 1; i <= n; i++) cin >> fa[i], graph[fa[i]].push_back(i), indeg[fa[i]]++;
    for (int i = 1; i <= n; i++) cin >> w[i];

    vector<int> lis;
    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        lis.push_back(p);
        if (!--indeg[fa[p]]) que.push(fa[p]);
    }
    reverse(lis.begin(), lis.end());

    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) continue;
        vector<int> ring;
        int tp = i;
        ring.push_back(tp), tp = fa[tp], indeg[tp]--;
        while (tp != i) ring.push_back(tp), tp = fa[tp], indeg[tp]--;
        reverse(ring.begin(), ring.end());

        if (ring.size() == 1) continue;

        int m = ring.size(), p = -1;

        for (int i = 0; i < m && p == -1; i++) {
            int pre = (i + m - 1) % m;
            if (a[ring[pre]] > a[ring[i]] || a[ring[pre]] + w[ring[pre]] <= a[ring[i]]) {
                p = i;
                break;
            }
        }

        if (p == -1) continue;

        if (a[fa[ring[p]]] > a[ring[p]]) f[ring[p]] = 1;
        for (int i = (p + 1) % m; i != p; i = (i + 1) % m) {
            int p = ring[i];
            if (a[fa[p]] > a[p])
                f[p] = 1;
            else if (a[fa[p]] + w[fa[p]] > a[p] && f[fa[p]])
                f[p] = f[fa[p]] + 1;
            else
                f[p] = 0;
        }
    }

    for (auto p : lis)
        if (a[fa[p]] > a[p])
            f[p] = 1;
        else if (a[fa[p]] + w[fa[p]] > a[p] && f[fa[p]])
            f[p] = f[fa[p]] + 1;
        else
            f[p] = 0;

    for (int i = 1; i <= n; i++) cout << (a[i] + (f[i] ? ifac[f[i]] : 0) * w[i]) % mod << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
