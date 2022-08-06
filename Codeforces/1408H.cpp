/**
 * @file 1408H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-04
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

typedef pair<int, int> pii;

class SegmentTree {
   private:
    int tree[maxn << 2], laz[maxn << 2], n;

    void pushDown(int p) { return dec(p << 1, laz[p]), dec(p << 1 | 1, laz[p]), laz[p] = 0, void(); }
    void pushUp(int p) { return tree[p] = min(tree[p << 1], tree[p << 1 | 1]), void(); }
    void dec(int p, int v = -1) { return tree[p] += v, laz[p] += v, void(); }
    void build(int p, int l, int r) {
        laz[p] = 0;
        if (l == r) return tree[p] = l, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void dec(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return dec(p);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) dec(p << 1, l, mid, ql, qr);
        if (qr > mid) dec(p << 1 | 1, mid + 1, r, ql, qr);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 0, n); }
    void update(int l) { return dec(1, 0, n, l, n); }
    int query(void) { return tree[1]; }
} ST;

int a[maxn], pre[maxn];
map<int, pii> vals;
vector<int> pts[maxn];

void solve(void) {
    int n, cnt0 = 0, mid = 0, cnt = 0;
    cin >> n;
    vals.clear();
    for (int i = 1; i <= n; i++) cin >> a[i], cnt0 += (a[i] == 0);
    while (cnt < (cnt0 + 1) / 2) cnt += (a[++mid] == 0);
    pre[0] = pre[n + 1] = 0;
    for (int i = 1; i <= mid; i++) pre[i] = pre[i - 1] + (a[i] == 0);
    for (int i = n; i > mid; i--) pre[i] = pre[i + 1] + (a[i] == 0);
    for (int i = 1; i <= mid; i++)
        if (a[i]) vals[a[i]].first = max(vals[a[i]].first, pre[i]);
    for (int i = mid + 1; i <= n; i++)
        if (a[i]) vals[a[i]].second = max(vals[a[i]].second, pre[i]);
    for (int i = 0; i <= pre[mid]; i++) pts[i].clear();
    for (auto i : vals) pts[i.second.first].push_back(i.second.second);
    ST.resize(pre[mid + 1]), ST.build();
    int ans = INT_MAX;
    for (int x = 0; x <= pre[mid]; x++) {
        for (auto i : pts[x])
            if (i <= pre[mid + 1]) ST.update(i);
        ans = min(ans, x + (int)vals.size() + ST.query());
    }
    cout << min(ans, cnt0 / 2) << endl;
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