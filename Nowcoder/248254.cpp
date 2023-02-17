/**
 * @file 248254.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-16
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

#define maxn 200005
#define mod 998244353

typedef pair<int, int> pii;

int64_t pw2[maxn];

class UnionSet {
   private:
    int fa[maxn], siz[maxn];
    stack<pii> S;

    int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }

   public:
    UnionSet(void) {
        for (int i = 0; i < maxn; i++) fa[i] = i, siz[i] = 1;
        return;
    }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    bool merge(int x, int y) {
        if (check(x, y)) return S.emplace(0, 0), false;
        x = getfa(x), y = getfa(y);
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y], fa[y] = x;
        return S.emplace(x, y), true;
    }
    void back(void) {
        int x, y;
        tie(x, y) = S.top(), S.pop();
        siz[x] -= siz[y], fa[y] = y;
        return;
    }
} US;

int tot, ans[maxn];

class SegmentTree {
   private:
    int n;
    vector<pii> ops[maxn << 2];

    void insert(int p, int l, int r, int ql, int qr, pii v) {
        if (ql <= l && r <= qr) return ops[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void solve(int p, int l, int r) {
        int tot_ = tot;
        for (auto i : ops[p]) tot += !US.merge(i.first, i.second);
        if (l == r) ans[l] = pw2[tot];
        if (l < r) {
            int mid = (l + r) >> 1;
            solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
        }
        for (int i = 0; i < (int)ops[p].size(); i++) US.back();
        tot = tot_;
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, pii v) { return insert(1, 1, n, l, r, v); }
    void solve(void) { return solve(1, 1, n); }
} ST;

map<pii, int> last;

void solve(void) {
    int n, m;
    cin >> n >> m, ST.resize(m);
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if (last.count({x, y}))
            ST.insert(last[{x, y}], i - 1, {x, y}), last.erase({x, y});
        else
            last[{x, y}] = i;
    }
    for (auto i : last) ST.insert(i.second, m, i.first);
    ST.solve();
    for (int i = 1; i <= m; i++) cout << (ans[i] + mod - 1) % mod << endl;
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pw2[0] = 1;
    for (int i = 1; i < maxn; i++) pw2[i] = pw2[i - 1] * 2 % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}