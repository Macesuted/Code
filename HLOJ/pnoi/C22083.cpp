/**
 * @file C22083.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-23
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
#define maxk 405

int n, m, k;
vector<vector<int>> graph;

class Tree {
   private:
    vector<bitset<maxk>> tl[maxn << 2], tr[maxn << 2];

    void build(int p, int l, int r) {
        if (l == r) return;
        int mid = (l + r) >> 1, pl = max(mid - k + 1, l), pr = min(mid + k, r);
        tr[p].resize(pr - l + 1), tl[p].resize(r - pl + 1);
        for (int i = pl; i <= pr; i++) tr[p][i - l][i - pl] = true;
        for (int i = pr; i > l; i--)
            for (auto j : graph[i])
                if (l <= j && j < i) tr[p][j - l] |= tr[p][i - l];
        for (int i = pl; i <= pr; i++) tl[p][i - pl][i - pl] = true;
        for (int i = pl; i < r; i++)
            for (auto j : graph[i])
                if (i < j && j <= r) tl[p][j - pl] |= tl[p][i - pl];
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return;
    }
    bool query(int p, int l, int r, int ql, int qr) {
        if (l == r) return true;
        int mid = (l + r) >> 1, pl = max(mid - k + 1, l), pr = min(mid + k, r);
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        for (int i = max(ql, pl); i <= min(qr, pr); i++)
            if (tr[p][ql - l][i - pl] && tl[p][qr - pl][i - pl]) return true;
        return false;
    }

   public:
    void build(void) { return build(1, 1, n); }
    bool query(int l, int r) { return query(1, 1, n, l, r); }
} tree;

void solve(void) {
    cin >> n >> m >> k, graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    tree.build();
    int q, cnt = 0;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x = (((int64_t)cnt * cnt) ^ x) % n + 1, y = (((int64_t)cnt * cnt) ^ y) % n + 1;
        if (x > y) swap(x, y);
        if (tree.query(x, y))
            cout << "Yes" << endl, cnt++;
        else
            cout << "No" << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("boat.in", "r", stdin), freopen("boat.out", "w", stdout);
#endif
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