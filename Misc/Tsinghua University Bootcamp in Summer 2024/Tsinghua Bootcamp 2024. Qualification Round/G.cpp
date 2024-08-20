/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-21
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

#define maxn 250005
#define mod 998244353

typedef pair<int, int> pii;
typedef tuple<bool, int, int> tbii;

class UnionSet {
   private:
    int n, fa[maxn << 1], siz[maxn << 1];
    stack<pii> log;

   public:
    void resize(int _n) { return n = _n, void(); }
    void init(void) {
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    }
    int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }

    void merge(int x, int y) {
        x = getfa(x), y = getfa(y);
        if (x == y) return log.emplace(-1, -1), void();
        if (siz[x] > siz[y]) swap(x, y);
        fa[x] = y, siz[y] += siz[x], log.emplace(x, y);
        return;
    }
    void back(void) {
        auto [x, y] = log.top();
        log.pop();
        if (x == y) return;
        fa[x] = x, siz[y] -= siz[x];
        return;
    }
} US;

class SegmentTree {
   private:
    vector<tbii> tree[maxn << 2];
    UnionSet US;
    int n, m;

    void insert(int p, int l, int r, int ql, int qr, tbii v) {
        if (ql <= l && r <= qr) return tree[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    int solve(int p, int l, int r) {
        int ans = 0, opt = 0;
        bool failed = false;
        for (auto [rev, x, y] : tree[p])
            if (rev) {
                if (US.getfa(x) == US.getfa(y)) {
                    failed = true;
                    break;
                }
                US.merge(x, y + n), US.merge(x + n, y), opt += 2;
            } else {
                if (US.getfa(x) == US.getfa(y + n)) {
                    failed = true;
                    break;
                }
                US.merge(x, y), US.merge(x + n, y + n), opt += 2;
            }
        if (!failed) {
            if (l == r)
                ans = 1;
            else {
                int mid = (l + r) >> 1;
                ans = solve(p << 1, l, mid) + solve(p << 1 | 1, mid + 1, r);
            }
        }
        while (opt--) US.back();
        return ans;
    }

   public:
    void resize(int _n, int _m) { return n = _n, m = _m, US.resize(n << 1), US.init(), void(); }
    void insert(int l, int r, tbii v) { return insert(1, 0, m, l, r, v); }
    int solve(void) { return solve(1, 0, m); }
} ST;

int p[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 2; i <= n; i++) cin >> p[i];

    int cnt = -1;
    US.resize(n), US.init(), ST.resize(n, m);
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, ST.insert(0, i - 1, {true, x, y}), ST.insert(i, m, {false, x, y}), US.merge(x, y);
    for (int i = 1; i <= n; i++)
        if (US.getfa(i) == i) cnt++;

    int64_t ans = 1;
    while (cnt--) ans = ans * 2 % mod;
    cout << ans * ST.solve() % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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