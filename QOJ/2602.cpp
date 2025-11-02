/**
 * @file 2602.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

using pii = pair<int, int>;

class SegmentTree {
   private:
    int sum[maxn << 2], val[maxn << 2];
    int n;

    void pushUp(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        val[p] = min(val[p << 1] + sum[p << 1 | 1], val[p << 1 | 1]);
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) return sum[p] = +1, val[p] = 0, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return val[p] = min(0, sum[p] += v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(void) { return val[1]; }
} SGT;

vector<pii> ins[maxn], del[maxn];
vector<int> pos[maxn];
int vmax[maxn][2];
bool mark[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1, c, l, r; i <= m; i++) cin >> c >> l >> r, ins[l].emplace_back(c, i), del[r].emplace_back(c, i);

    multiset<pii> S;
    for (int i = 1; i <= n; i++) {
        for (auto v : ins[i]) S.insert(v);

        vmax[i][0] = vmax[i][1] = 1;
        if (S.size() >= 1) vmax[i][0] = S.rbegin()->first, pos[S.rbegin()->second].push_back(i);
        if (S.size() >= 2) vmax[i][1] = next(S.rbegin())->first;

        for (auto v : del[i]) S.erase(S.find(v));
    }

    SGT.resize(n), SGT.build();

    for (int i = 1; i <= n; i++) SGT.update(vmax[i][0], -1);

    auto check = [&](void) -> void {
        if (SGT.query() != 0) return;

        set<int> S;
        for (int i = 1; i <= n; i++) S.insert(i);

        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) {
            auto p = S.lower_bound(vmax[i][mark[i]]);
            cout << *p << ' ', S.erase(p);
        }
        cout << endl;

        exit(0);
    };

    check();

    for (int i = 1; i <= m; i++) {
        for (auto p : pos[i]) mark[p] = true, SGT.update(vmax[p][0], +1), SGT.update(vmax[p][1], -1);
        check();
        for (auto p : pos[i]) mark[p] = false, SGT.update(vmax[p][0], -1), SGT.update(vmax[p][1], +1);
    }

    cout << "NO" << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
