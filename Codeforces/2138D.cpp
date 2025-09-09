/**
 * @file 2138D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 10005
#define mod 1'000'000'007

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int a[maxn];
int64_t fac[maxn], inv[maxn];
pii ques[maxn];
int du[maxn], dd[maxn];
vector<int> rec[maxn];

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> val;
    for (int i = 1; i <= n; i++) cin >> a[i], rec[i].clear(), val.push_back(a[i] - i);

    for (int i = 1, x, y; i <= q; i++) cin >> x >> y, ques[i] = {x, y}, val.push_back(y - x);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < (int)val.size(); i++) dd[i] = du[i] = 0;

    for (int i = 1; i <= q; i++) {
        int v = lower_bound(val.begin(), val.end(), ques[i].second - ques[i].first) - val.begin();
        rec[ques[i].first].push_back(v), dd[v]++;
    }

    int ou = 0, od = 0;

    for (int p = 1; p <= n; p++) {
        int64_t ans = 1;

        for (auto v : rec[p - 1]) dd[v]--;
        for (auto v : rec[p]) ou++, du[v]--;

        int vu = 0, vd = 0;

        auto calc = [&](int l, int r, int du, int dd) -> void {
            vu += du, vd += dd;
            if (l >= r) return;
            int64_t ret = vu % mod * inv[vu + vd] % mod;
            if (l + p < a[p] && !vu && !vd) ret = 1;
            ans = (ans + ret * (r - l)) % mod;
            return;
        };

        calc(1 - p, val[0], ou, od);
        for (int i = 0; i + 1 < (int)val.size(); i++) calc(val[i], val[i + 1], du[i], dd[i]);
        calc(val[val.size() - 1], m - p, du[val.size() - 1], dd[val.size() - 1]);

        cout << ans * fac[q] % mod << ' ';
    }
    cout << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod, inv[i] = qpow(i, mod - 2);

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}