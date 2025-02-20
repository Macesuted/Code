/**
 * @file 2066E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-19
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

#define maxn 1000005

class FenwickTree {
   private:
    int64_t a[maxn];

   public:
    void add(int p, int64_t v) {
        for (int i = p; i < maxn; i += i & -i) a[i] += v;
        return;
    }
    int64_t query(int p) {
        int64_t ans = 0;
        for (int i = min(p, maxn - 1); i; i -= i & -i) ans += a[i];
        return ans;
    }
} FT;

class SegmentTree {
   private:
    int n, gap[maxn << 2];

    void pushUp(int p) { return gap[p] = min(gap[p << 1], gap[p << 1 | 1]), void(); }
    void build(int p, int l, int r) {
        if (l == r) return gap[p] = INT_MAX, void();
        int mid = (l + r) >> 1;
        return build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r), pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return gap[p] = v, void();
        int mid = (l + r) >> 1;
        return qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v), pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr, int qv) {
        if (gap[p] > qv) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1, ans = -1;
        if (qr > mid) ans = query(p << 1 | 1, mid + 1, r, ql, qr, qv);
        if (ql <= mid && ans == -1) ans = query(p << 1, l, mid, ql, qr, qv);
        return ans;
    }

   public:
    SegmentTree() { build(1, 1, n = 1e6); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r, int v) { return query(1, 1, n, l, r, v); }
} SGT;

map<int, int> S;
set<int> V0;

void insert(int v) {
    S[v]++, FT.add(v, +v);
    if (S[v] == 2) V0.insert(v);
    if (S[v] >= 2) return;
    auto p = S.find(v);
    if (p != S.begin()) SGT.update(v, v - prev(p)->first);
    if (next(p) != S.end()) SGT.update(next(p)->first, next(p)->first - v);
    return;
}
void erase(int v) {
    S[v]--, FT.add(v, -v);
    if (S[v] == 1) V0.erase(v);
    if (S[v]) return;
    SGT.update(v, INT_MAX), S.erase(v);
    auto p = S.lower_bound(v);
    if (p != S.begin() && p != S.end()) SGT.update(p->first, p->first - prev(p)->first);
    return;
}

bool check(void) {
    if (S.size() == 1 && S.begin()->second == 1) return true;
    if (V0.empty()) return false;
    int v = *V0.rbegin();
    int64_t sum = FT.query(maxn - 1) - S.rbegin()->first, cur = FT.query(v);
    while (cur < sum) {
        int64_t nxt = FT.query(cur);
        if (nxt != cur) {
            v = cur, cur = nxt;
            continue;
        }

        v = SGT.query(S.upper_bound(v)->first + 1, 1e6, cur);
        if (v == -1) return false;
        cur = FT.query(v);
    }
    return true;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1, v; i <= n; i++) cin >> v, insert(v);
    cout << (check() ? "Yes" : "No") << endl;
    while (q--) {
        char op;
        int v;
        cin >> op >> v;
        op == '+' ? insert(v) : erase(v);
        cout << (check() ? "Yes" : "No") << endl;
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}