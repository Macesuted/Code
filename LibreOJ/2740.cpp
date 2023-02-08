/**
 * @file 2740.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-08
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

#define maxn 400005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    pii tree[maxn << 2];
    int n;

    pii merge(pii a, pii b) { return {a.first + b.first, min(a.second, a.first + b.second)}; }
    void pushUp(int p) { return tree[p] = merge(tree[p << 1], tree[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = {v, min(0, v)}, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
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
    void update(int p, int v) { return update(1, 1, n, p, v); }
    pii query(int l, int r) { return l > r ? pii{0, 0} : query(1, 1, n, l, r); }
} ST;

pii a[maxn];
stack<int> S[maxn >> 1];

void solve(void) {
    int n;
    cin >> n, ST.resize(2 * n);
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 1; i <= n; i++) cin >> a[n + i].first >> a[n + i].second, a[n + i].first *= -1;
    sort(a + 1, a + 2 * n + 1, [](const pii& a, const pii& b) {
        return a.second < b.second || (a.second == b.second && a.first > 0 && b.first < 0);
    });
    int ans = n;
    for (int i = 1; i <= 2 * n; i++) {
        ST.update(i, a[i].first / abs(a[i].first));
        if (a[i].first > 0) {
            S[a[i].first].push(i);
            continue;
        }
        if (!S[-a[i].first].empty()) {
            int p = S[-a[i].first].top();
            if (ST.query(1, p - 1).first + ST.query(p + 1, i - 1).second >= 0)
                ans--, S[-a[i].first].pop(), ST.update(p, 0), ST.update(i, 0);
        }
    }
    cout << ans << endl;
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