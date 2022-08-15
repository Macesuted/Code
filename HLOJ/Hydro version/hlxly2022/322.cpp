/**
 * @file 322.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-14
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

typedef pair<int, int> pii;
typedef pair<double, int> pdi;

pdi val[maxn];

class SegmentTree {
   private:
    pii a[maxn << 2];
    int n;

    double getVal(pii a, int v) { return a.first * val[v].first + a.second; }
    void insert(int p, int l, int r, pii v) {
        int mid = (l + r) >> 1;
        if (a[p] == pii{0, 0}) return a[p] = v, void();
        if (getVal(a[p], mid) < getVal(v, mid)) swap(a[p], v);
        if (l == r) return;
        if (getVal(a[p], l) < getVal(v, l)) insert(p << 1, l, mid, v);
        if (getVal(a[p], r) < getVal(v, r)) insert(p << 1 | 1, mid + 1, r, v);
        return;
    }
    double query(int p, int l, int r, int qp) {
        if (l == r) return a[p].first * val[qp].first + a[p].second;
        int mid = (l + r) >> 1;
        return max(a[p].first * val[qp].first + a[p].second,
                   qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(pii v) { return insert(1, 1, n, v); }
    double query(int v) { return query(1, 1, n, v); }
} ST;

int x[maxn], y[maxn], a[maxn], b[maxn], len[maxn], sumS[maxn], sumT[maxn], pv[maxn];

void solve(void) {
    string S, T;
    int n, m;
    cin >> S >> n;
    for (int i = 0; i < (int)S.size(); i++) sumS[i + 1] = sumS[i] + (S[i] == '0');
    for (int i = 1, l, r; i <= n; i++) cin >> l >> r, x[i] = sumS[r] - sumS[l - 1], y[i] = r - l + 1 - x[i];
    cin >> T >> m;
    for (int i = 0; i < (int)T.size(); i++) sumT[i + 1] = sumT[i] + (T[i] == '0');
    for (int i = 1, ql, qr, px, py; i <= m; i++)
        cin >> ql >> qr, len[i] = qr - ql + 1, px = sumT[qr] - sumT[ql - 1], py = len[i] - px, a[i] = len[i] + 1 - px,
                         b[i] = len[i] + 1 - py, val[i] = {1. * b[i] / a[i], i};
    sort(val + 1, val + m + 1), ST.resize(m);
    for (int i = 1; i <= m; i++) pv[val[i].second] = i;
    for (int i = 1; i <= n; i++) ST.insert({y[i], x[i]});
    for (int i = 1; i <= m; i++) cout << (int64_t)round(ST.query(pv[i]) * a[i]) + len[i] + 1 << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("A.in", "r", stdin), freopen("A.out", "w", stdout);
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