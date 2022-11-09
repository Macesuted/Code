/**
 * @file 266.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define mod 998244353

typedef pair<int, int> pii;
typedef tuple<bool, int, int, int> tbiii;

class SegmentTree {
   private:
    set<pii> tree[maxn << 2];
    int n;

    void clear(int p, int l, int r) {
        tree[p].clear();
        if (l == r) return;
        int mid = (l + r) >> 1;
        clear(p << 1, l, mid), clear(p << 1 | 1, mid + 1, r);
        return;
    }
    void insert(int p, int l, int r, int ql, int qr, pii v) {
        if (ql <= l && r <= qr) return tree[p].insert(v), void();
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void erase(int p, int l, int r, int ql, int qr, pii v) {
        if (ql <= l && r <= qr) return tree[p].erase(v), void();
        int mid = (l + r) >> 1;
        if (ql <= mid) erase(p << 1, l, mid, ql, qr, v);
        if (qr > mid) erase(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    vector<int> ans;
    void query(int p, int l, int r, int qp, int ql, int qr) {
        for (auto i = tree[p].lower_bound({ql, 0}); i != tree[p].end() && i->first <= qr; i++) ans.push_back(i->second);
        if (l == r) return;
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp, ql, qr) : query(p << 1 | 1, mid + 1, r, qp, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void clear(void) { return clear(1, 1, n); }
    void insert(int l, int r, pii v) { return insert(1, 1, n, l, r, v); }
    void erase(int l, int r, pii v) { return erase(1, 1, n, l, r, v); }
    vector<int> query(int p, int l, int r) { return ans.clear(), query(1, 1, n, p, l, r), ans; }
} ST[2];

vector<int> pts[2][maxn], dist;
vector<tbiii> blk;
queue<int> que;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) pts[0][i].clear(), pts[1][i].clear();
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, pts[0][y].push_back(x), pts[1][x].push_back(y);
    ST[0].resize(n), ST[1].resize(n), ST[0].clear(), ST[1].clear(), blk.clear();
    for (int t = 0; t < 2; t++)
        for (int i = 1; i <= n; i++) {
            pts[t][i].push_back(0), pts[t][i].push_back(n + 1);
            sort(pts[t][i].begin(), pts[t][i].end());
            for (int j = 1; j < (int)pts[t][i].size(); j++) {
                int l = pts[t][i][j - 1] + 1, r = pts[t][i][j] - 1;
                if (l > r) continue;
                ST[!t].insert(l, r, {i, blk.size()}), blk.emplace_back(t, l, r, i);
            }
        }
    dist.resize(blk.size());
    for (int i = 1; i < (int)dist.size(); i++) dist[i] = INT_MAX;
    dist[0] = 0, que.push(0), ST[1].erase(get<1>(blk[0]), get<2>(blk[0]), {get<3>(blk[0]), 0});
    int64_t ans = 0;
    while (!que.empty()) {
        int p = que.front(), l, r, c;
        bool t;
        que.pop();
        tie(t, l, r, c) = blk[p];
        ans = (ans + (int64_t)dist[p] * (dist[p] - 1) / 2 % mod * (r - l + 1)) % mod;
        vector<int> ret = ST[t].query(c, l, r);
        for (auto i : ret) ST[t].erase(get<1>(blk[i]), get<2>(blk[i]), {get<3>(blk[i]), i}), dist[i] = dist[p] + 1, que.push(i);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("light.in", "r", stdin), freopen("light.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}