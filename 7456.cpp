/**
 * @file 7456.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
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

#define maxn 50005
#define maxd 105

typedef pair<int64_t, int64_t> pll;

const int64_t base1 = 1331, base2 = 13331, mod1 = 1000000007, mod2 = 998244353;

map<pll, int> cnt;

int64_t pow1[maxd], pow2[maxd];
pll val[maxn];
int fa[maxd][maxn], siz[maxd][maxn];
vector<int> rec[maxd][maxn];
int64_t ans;
int D;

void update(pll x, int v) {
    ans -= (int64_t)cnt[x] * (cnt[x] - 1) / 2;
    cnt[x] += v;
    ans += (int64_t)cnt[x] * (cnt[x] - 1) / 2;
    if (!cnt[x]) cnt.erase(x);
    return;
}
int getfa(int d, int p) { return fa[d][p] == p ? p : fa[d][p] = getfa(d, fa[d][p]); }
void merge(int d, int x, int y) {
    x = getfa(d, x), y = getfa(d, y);
    if (x == y) return;
    if (siz[d][x] > siz[d][y]) swap(x, y);
    fa[d][x] = y, siz[d][y] += siz[d][x];
    for (auto i : rec[d][x]) {
        rec[d][y].push_back(i);
        update(val[i], -1);
        val[i].first = (val[i].first + (y + mod1 - x) * pow1[D - d]) % mod1;
        val[i].second = (val[i].second + (y + mod2 - x) * pow2[D - d]) % mod2;
        update(val[i], +1);
    }
    rec[d][x].clear();
    return;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> D >> k;

    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= D; i++) pow1[i] = pow1[i - 1] * base1 % mod1, pow2[i] = pow2[i - 1] * base2 % mod2;

    for (int i = 1; i <= n; i++) rec[0][i].clear(), rec[0][i].push_back(i), fa[0][i] = i, siz[0][i] = 1;

    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, merge(0, x, y);

    for (int i = 1; i <= D; i++)
        for (int j = 1; j <= n; j++) rec[i][j] = rec[0][j], fa[i][j] = fa[0][j], siz[i][j] = siz[0][j];

    ans = 0, cnt.clear();

    for (int i = 1; i <= n; i++) {
        int64_t v1 = 0, v2 = 0;
        for (int j = 0; j <= D; j++) v1 = (v1 * base1 + getfa(j, i)) % mod1, v2 = (v2 * base2 + getfa(j, i)) % mod2;
        update(val[i] = {v1, v2}, +1);
    }

    while (k--) {
        int x, y, d;
        cin >> x >> y >> d;
        merge(d - 1, x, y);
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

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}