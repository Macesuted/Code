/**
 * @file H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using int128_t = __int128_t;

bool mem1;

class SegmentTree {
   private:
    struct Node {
        int128_t sum;
        int64_t deltSum, cnt;
        int l, r, deltCnt, laz;
        bool cls;
        Node(void) { l = r = 0, sum = cnt = deltSum = deltCnt = laz = 0, cls = false; }
    };

    Node a[15000000];
    int pos;

    int root;
    const int64_t n = 1e12;

    int newNode(void) { return a[++pos] = Node(), pos; }

    void pushDown(int p) {
        if (!a[p].l) a[p].l = newNode();
        if (!a[p].r) a[p].r = newNode();
        int l = a[p].l, r = a[p].r;
        if (a[p].cls) {
            a[l].sum = a[l].cnt = a[l].laz = 0, a[l].cls = true;
            a[r].sum = a[r].cnt = a[r].laz = 0, a[r].cls = true;
            a[p].cls = false;
        }
        if (a[p].laz) {
            a[l].sum += a[p].laz * (int128_t)a[l].deltSum, a[l].cnt += a[p].laz * (int64_t)a[l].deltCnt, a[l].laz += a[p].laz;
            a[r].sum += a[p].laz * (int128_t)a[r].deltSum, a[r].cnt += a[p].laz * (int64_t)a[r].deltCnt, a[r].laz += a[p].laz;
            a[p].laz = 0;
        }
        return;
    }
    void pushUp(int p) {
        a[p].sum = a[p].cnt = 0;
        if (a[p].l) a[p].sum += a[a[p].l].sum, a[p].cnt += a[a[p].l].cnt;
        if (a[p].r) a[p].sum += a[a[p].r].sum, a[p].cnt += a[a[p].r].cnt;
        return;
    }

    void addLaz(int& p, int64_t l, int64_t r, int64_t qp) {
        if (!p) p = newNode();
        a[p].deltSum += qp, a[p].deltCnt++;
        if (l == r) return;
        int64_t mid = (l + r) >> 1;
        qp <= mid ? addLaz(a[p].l, l, mid, qp) : addLaz(a[p].r, mid + 1, r, qp);
        return;
    }
    void insert(int& p, int64_t l, int64_t r, int64_t qp) {
        if (!p) p = newNode();
        if (l == r) return a[p].sum += l, a[p].cnt++, void();
        pushDown(p);
        int64_t mid = (l + r) >> 1;
        qp <= mid ? insert(a[p].l, l, mid, qp) : insert(a[p].r, mid + 1, r, qp);
        return pushUp(p);
    }
    int64_t query(int& p, int64_t l, int64_t r, int64_t& v) {
        if (!p) return 0;
        if (a[p].sum <= v) {
            int64_t ret = a[p].cnt;
            v -= a[p].sum, a[p].sum = a[p].cnt = a[p].laz = 0, a[p].cls = true;
            return ret;
        }
        if (l == r) {
            int64_t ret = v / l;
            a[p].sum -= l * ret, a[p].cnt -= ret, v -= ret * l;
            if (v) a[p].sum -= l, a[p].cnt--, insert(root, 1, n, l - v), v = 0;
            return ret;
        }
        pushDown(p);
        int64_t mid = (l + r) >> 1, ans = 0;
        ans += query(a[p].l, l, mid, v);
        if (v) ans += query(a[p].r, mid + 1, r, v);
        return pushUp(p), ans;
    }

   public:
    SegmentTree(void) { pos = 0, root = newNode(); }
    void addLaz(int64_t p) { return addLaz(root, 1, n, p); }
    void genLaz(void) { return a[root].sum += a[root].deltSum, a[root].cnt += a[root].deltCnt, a[root].laz++, void(); }
    int64_t query(int64_t v) { return query(root, 1, n, v); }
} SGT;

#define maxn 300005

int64_t a[maxn], c[maxn], ans[maxn];

bool mem2;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> c[i], SGT.addLaz(c[i]);

    ans[n + 1] = 0;
    for (int i = n; i; i--) {
        SGT.genLaz();
        ans[i] = ans[i + 1] + SGT.query(a[i]);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}