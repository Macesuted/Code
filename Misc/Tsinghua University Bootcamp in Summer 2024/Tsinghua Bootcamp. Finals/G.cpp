/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005
#define maxv 1000005

typedef pair<int64_t, int> pli;

class SegmentTree2 {
   private:
    int64_t sum[maxn << 2];
    int len[maxn << 2], n;

    void pushUp(int p) {
        len[p] = len[p << 1] + len[p << 1 | 1];
        sum[p] = sum[p << 1] + ((len[p << 1] & 1) ? -1 : +1) * sum[p << 1 | 1];
        return;
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return sum[p] = v, len[p] = (v > 0), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    pli query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return {sum[p], len[p]};
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        pli retl = query(p << 1, l, mid, ql, qr), retr = query(p << 1 | 1, mid + 1, r, ql, qr);
        return {retl.first + ((retl.second & 1) ? -1 : +1) * retr.first, retl.second + retr.second};
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r).first; }
};

SegmentTree2 ST2[8];

vector<int> pos;
class SegmentTree1 {
   private:
    int val[maxn << 2], n;

    void pushUp(int p) { return val[p] = min(val[p << 1], val[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return val[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void getPos(int p, int l, int r, int ql, int qr, int lim) {
        if (val[p] > lim) return;
        if (l == r) return pos.push_back(l);
        int mid = (l + r) >> 1;
        if (ql <= mid) getPos(p << 1, l, mid, ql, qr, lim);
        if (qr > mid) getPos(p << 1 | 1, mid + 1, r, ql, qr, lim);
        return;
    }

   public:
    void resize(int _n) {
        n = _n;
        for (int i = 0; i < 8; i++) ST2[i].resize(n);
        return;
    }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    void getPos(int l, int r, int lim) { return pos.clear(), getPos(1, 1, n, l, r, lim); }
};

SegmentTree1 ST;

vector<int> prime;
int fap[maxv], a[maxn], cnt[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    ST.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i], ST.update(i, a[i]);
        int v = a[i];
        while (v > 1) {
            int x = fap[v];
            cnt[i]++;
            while (v % x == 0) v /= x;
        }
        for (int j = cnt[i]; j < 8; j++) ST2[j].update(i, a[i]);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k, k = min(k, 7);
            cout << ST2[k].query(l, r) << endl;
        } else if (op == 2) {
            int p, x;
            cin >> p >> x;
            for (int i = cnt[p]; i < 8; i++) ST2[i].update(p, 0);
            cnt[p] = 0, a[p] = x;
            while (x > 1) {
                int v = fap[x];
                cnt[p]++;
                while (x % v == 0) x /= v;
            }
            for (int i = cnt[p]; i < 8; i++) ST2[i].update(p, a[p]);
            ST.update(p, a[p]);
        } else {
            int l, r, v, lim, tv;
            cin >> l >> r >> v >> lim, tv = v;
            if (v == 1) continue;
            vector<int> vals;
            while (tv > 1) {
                int x = fap[tv];
                vals.push_back(x);
                while (tv % x == 0) tv /= x;
            }
            ST.getPos(l, r, lim / v);
            for (auto i : pos) {
                for (int j = cnt[i]; j < 8; j++) ST2[j].update(i, 0);
                for (auto x : vals)
                    if (a[i] % x) cnt[i]++;
                ST.update(i, a[i] *= v);
                for (int j = cnt[i]; j < 8; j++) ST2[j].update(i, a[i]);
            }
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    fap[1] = 1;
    for (int i = 2; i < maxv; i++) {
        if (!fap[i]) prime.push_back(i), fap[i] = i;
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxv; j++) {
            fap[i * *j] = *j;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

    return 0;
}