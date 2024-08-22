/**
 * @file J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 100005

class SegmentTree {
   private:
    int64_t minv[maxn << 2], maxv[maxn << 2], sum[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p, int l, int r) {
        if (!laz[p]) return;
        int mid = (l + r) >> 1;
        sum[p << 1] += (mid - l + 1) * laz[p], minv[p << 1] += laz[p], maxv[p << 1] += laz[p], laz[p << 1] += laz[p];
        sum[p << 1 | 1] += (r - mid) * laz[p], minv[p << 1 | 1] += laz[p], maxv[p << 1 | 1] += laz[p],
            laz[p << 1 | 1] += laz[p];
        laz[p] = 0;
        return;
    }
    void pushUp(int p) {
        minv[p] = min(minv[p << 1], minv[p << 1 | 1]), maxv[p] = max(maxv[p << 1], maxv[p << 1 | 1]);
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        return;
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return minv[p] = maxv[p] = sum[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void add(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return minv[p] += v, maxv[p] += v, laz[p] += v, sum[p] += (r - l + 1) * v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void div(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr && minv[p] == maxv[p]) {
            int64_t d = minv[p] / v, val = (minv[p] > 0) ? d : (d - (v * d != minv[p]));
            laz[p] += val - minv[p], sum[p] += (r - l + 1) * (val - minv[p]), minv[p] = maxv[p] = val;
            return;
        }
        if (ql <= l && r <= qr && minv[p] + 1 == maxv[p]) {
            int64_t d = minv[p] / v, val = (minv[p] > 0) ? d : (d - (v * d != minv[p]));
            int64_t _d = maxv[p] / v, _val = (maxv[p] > 0) ? _d : (_d - (v * _d != maxv[p]));
            if (minv[p] - val == maxv[p] - _val) {
                laz[p] += val - minv[p], sum[p] += (r - l + 1) * (val - minv[p]);
                minv[p] = val;
                maxv[p] = _val;
                return;
            }
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) div(p << 1, l, mid, ql, qr, v);
        if (qr > mid) div(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t getMin(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return minv[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return getMin(p << 1, l, mid, ql, qr);
        if (ql > mid) return getMin(p << 1 | 1, mid + 1, r, ql, qr);
        return min(getMin(p << 1, l, mid, ql, qr), getMin(p << 1 | 1, mid + 1, r, ql, qr));
    }
    int64_t getSum(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return getSum(p << 1, l, mid, ql, qr);
        if (ql > mid) return getSum(p << 1 | 1, mid + 1, r, ql, qr);
        return getSum(p << 1, l, mid, ql, qr) + getSum(p << 1 | 1, mid + 1, r, ql, qr);
    }
    void print(int p, int l, int r) {
        if (l == r) {
            cerr << l << ' ' << r << ' ' << sum[p] << ' ' << minv[p] << ' ' << maxv[p] << endl;
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void add(int l, int r, int64_t v) { return add(1, 1, n, l, r, v); }
    void div(int l, int r, int64_t v) { return div(1, 1, n, l, r, v); }
    int64_t getMin(int l, int r) { return getMin(1, 1, n, l, r); }
    int64_t getSum(int l, int r) { return getSum(1, 1, n, l, r); }
    void print(void) { return print(1, 1, n); }
} ST;

int read(void) {
    char c = getchar();
    int64_t f = +1, x = 0;
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getchar();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * f;
}

int a[maxn];

void solve(void) {
    int n = read(), q = read();
    ST.resize(n);
    for (int i = 1; i <= n; i++) a[i] = read();
    ST.build(a);
    while (q--) {
        int op = read(), l = read(), r = read();
        if (op == 1)
            ST.add(l, r, read());
        else if (op == 2)
            ST.div(l, r, read());
        else if (op == 3)
            cout << ST.getMin(l, r) << endl;
        else
            cout << ST.getSum(l, r) << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}