/**
 * @file 6104.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-05
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

#define maxn 100005
#define maxk 12

using pii = pair<int, int>;

class SegmentTree {
   private:
    int a[maxn << 2], cnt[maxn << 2];
    int n;

    void pushUp(int p) {
        a[p] = min(a[p << 1], cnt[p << 1] + a[p << 1 | 1]);
        cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
        return;
    }

    void build(int p, int l, int r) {
        if (l == r) return cnt[p] = 0, a[p] = 1e9, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return a[p] = v, cnt[p]++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int qp, int rv = 1e9) {
        if (l == r) return rv;
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp, min(rv + cnt[p << 1 | 1], a[p << 1 | 1]))
                         : query(p << 1 | 1, mid + 1, r, qp, rv);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    int query(int p) { return query(1, 1, n, p); }
} SGT[maxk];

class FenwickTree {
   private:
    int a[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) a[i] += v;
        return;
    }
    int sum(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += a[i];
        return ans;
    }
} FT;

pii a[maxn];

void solve(void) {
    int n, L, K;
    cin >> n >> L >> K;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = -i;

    if (K == 1) {
        int ans = 0;
        for (int i = 1; i < L; i++) ans += a[i].first >= a[L].first;
        for (int i = L + 1; i <= n; i++) ans += a[i].first > a[L].first;
        return cout << ans << endl, void();
    }

    for (int t = 1; t < K; t++) SGT[t].resize(n), SGT[t].build();

    sort(a + 1, a + n + 1, greater<pii>());

    for (int i = 1; i <= n; i++) {
        int p = -a[i].second;

        if (p == L) {
            int ans = SGT[K - 1].query(L) + FT.sum(p);
            if (ans >= 1e9) return cout << -1 << endl, void();
            return cout << ans << endl, void();
        }

        for (int t = K - 2; t; t--) SGT[t + 1].insert(p, SGT[t].query(p));

        FT.add(p, +1);
        SGT[1].insert(p, i - FT.sum(p));
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