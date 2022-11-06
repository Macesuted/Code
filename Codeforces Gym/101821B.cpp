/**
 * @file 101821B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
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

#define maxn 500005
#define mod 998244353

typedef pair<int, int> pii;

int Mod(int x) { return x >= mod ? x - mod : x; }
int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

class SegmentTree {
   private:
    struct Node {
        int v, cnt, val1, val2;
    };
    Node tree[maxn << 2];

    Node merge(Node a, Node b) {
        return a.v != b.v ? (a.v > b.v ? a : b)
                          : Node{a.v, Mod(a.cnt + b.cnt), a.val1, (a.val1 == b.val1 ? max(a.val2, b.val2) : b.val1)};
    }
    void update(int p, int l, int r, int qp, pii v, pii val) {
        if (l == r)
            return tree[p].v = v.first, tree[p].cnt = v.second, tree[p].val1 = val.first, tree[p].val2 = val.second, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v, val) : update(p << 1 | 1, mid + 1, r, qp, v, val);
        return tree[p] = merge(tree[p << 1], tree[p << 1 | 1]), void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void clear(void) {
        for (int i = 0; i < (maxn << 2); i++) tree[i].v = tree[i].cnt = 0, tree[i].val1 = tree[i].val2 = -1;
        return;
    }
    void update(int p, pii v, pii val = {-1, -1}) { return update(1, 0, maxn - 1, p, v, val); }
    Node query(int l, int r) { return query(1, 0, maxn - 1, l, r); }
} ST;

int a[maxn], f[maxn];
bool ban[maxn];
pii fl[maxn], fr[maxn], g[maxn], gv[maxn], h[maxn];
vector<int> LIS, LDS;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ST.clear(), ST.update(n + 1, {0, 1});
    for (int i = 1; i <= n; i++) {
        auto ret = ST.query(a[i] + 1, n + 1);
        ST.update(a[i], fl[i] = {ret.v + 1, ret.cnt});
    }
    ST.clear(), ST.update(0, {0, 1});
    for (int i = n; i >= 1; i--) {
        auto ret = ST.query(0, a[i] - 1);
        ST.update(a[i], fr[i] = {ret.v + 1, ret.cnt});
    }
    int maxLDS = 0, maxLIS = 0, pos = 0, len, val = 0;
    for (int i = 1; i <= n; i++) maxLDS = max(maxLDS, fl[i].first);
    int64_t tot = 0;
    for (int i = 1; i <= n; i++)
        if (fl[i].first + fr[i].first - 1 == maxLDS) tot = Mod(tot + (f[i] = (int64_t)fl[i].second * fr[i].second % mod));
    tot = tot * Inv(maxLDS) % mod;
    ST.clear(), ST.update(0, {0, 1}, {0, -1});
    for (int i = 1; i <= n; i++) {
        auto ret = ST.query(0, a[i] - 1);
        g[i] = {ret.v + 1, ret.cnt};
        gv[i] = {ret.val1 == -1 ? -1 : Mod(ret.val1 + f[i]), ret.val2 == -1 ? -1 : Mod(ret.val2 + f[i])};
        ST.update(a[i], g[i], gv[i]);
    }
    for (int i = 1; i <= n; i++) maxLIS = max(maxLIS, g[i].first);
    for (int i = 1; i <= n; i++)
        if (g[i].first == maxLIS && (((~gv[i].first) && gv[i].first != tot) || ((~gv[i].second) && gv[i].second != tot)))
            pos = i, val = (((~gv[i].first) && gv[i].first != tot) ? gv[i].first : gv[i].second);
    if (!pos) return cout << "IMPOSSIBLE" << endl, void();
    len = maxLIS;
    while (len) {
        while (g[pos].first != len || (gv[pos].first != val && gv[pos].second != val)) pos--;
        len--, val = Mod(val + mod - f[pos]), ban[pos] = true, LIS.push_back(pos);
    }
    ST.clear(), ST.update(n + 1, {0, 0});
    for (int i = 1; i <= n; i++)
        if (!ban[i]) {
            auto ret = ST.query(a[i] + 1, n + 1);
            ST.update(a[i], {h[i].first = ret.v + 1, ret.cnt}, {i, -1}), h[i].second = ret.val1;
        }
    int maxSLDS = pos = 0;
    for (int i = 1; i <= n; i++)
        if (!ban[i]) maxSLDS = max(maxSLDS, h[i].first);
    for (int i = 1; i <= n; i++)
        if (!ban[i] && h[i].first == maxSLDS) pos = i;
    while (~pos) LDS.push_back(pos), pos = h[pos].second;
    reverse(LIS.begin(), LIS.end()), reverse(LDS.begin(), LDS.end());
    cout << maxLIS << endl;
    for (auto i : LIS) cout << i << ' ';
    cout << endl;
    cout << maxLDS << endl;
    for (auto i : LDS) cout << i << ' ';
    cout << endl;
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