/**
 * @file 1707E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-17
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Solution: https://macesuted.moe/article/cf1707e
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define maxlgn 18

typedef pair<int, int> pii;

pii merge(const pii& a, const pii& b) { return {min(a.first, b.first), max(a.second, b.second)}; }

class SegmentTree {
   private:
    pii tree[maxn << 2];
    int n;

    void pushUp(int p) { return tree[p] = merge(tree[p << 1], tree[p << 1 | 1]), void(); }
    void insert(int p, int l, int r, int qp, pii v) {
        if (l == r) return tree[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    pii query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int p, pii v) { return insert(1, 1, n, p, v); }
    pii query(pii a) { return a.first >= a.second ? pii{INT_MAX, INT_MIN} : query(1, 1, n, a.first, a.second - 1); }
};

int a[maxn];
SegmentTree ST[maxlgn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < maxlgn; i++) ST[i].resize(n);
    for (int i = 1; i < n; i++) ST[0].insert(i, {min(a[i], a[i + 1]), max(a[i], a[i + 1])});
    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j < n; j++) ST[i].insert(j, ST[i - 1].query(ST[i - 1].query({j, j + 1})));
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == 1 && r == n)
            cout << 0 << endl;
        else if (l == r)
            cout << -1 << endl;
        else {
            int ans = 0;
            for (int i = maxlgn - 1; ~i; i--) {
                pii ret = ST[i].query({l, r});
                if (ret != pii{1, n}) ans |= 1 << i, tie(l, r) = ret;
            }
            ans++;
            cout << (ans == (1 << maxlgn) ? -1 : ans) << endl;
        }
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