/**
 * @file 12955.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005

class SegmentTree {
   private:
    struct Node {
        int maxPre, minPre, sum, cnt;
        bool laz;
        Node operator+(const Node& o) const {
            return {max(maxPre, sum + o.maxPre), min(minPre, sum + o.minPre), sum + o.sum, cnt + o.cnt, false};
        }
    };

    Node tree[maxn << 2];
    int n;

    void upd(int p, int len) {
        return swap(tree[p].maxPre, tree[p].minPre), tree[p].maxPre = -tree[p].maxPre, tree[p].minPre = -tree[p].minPre,
                                                     tree[p].sum = -tree[p].sum, tree[p].cnt = len - tree[p].cnt,
                                                     tree[p].laz ^= true, void();
    }
    void pushDown(int p, int l, int r) {
        if (!tree[p].laz) return;
        int mid = (l + r) >> 1;
        upd(p << 1, mid - l + 1), upd(p << 1 | 1, r - mid), tree[p].laz = false;
        return;
    }
    void build(int p, int l, int r, string& s) {
        if (l == r)
            return tree[p].sum = (s[l] == 'A' ? +1 : -1), tree[p].minPre = min(0, tree[p].sum),
                   tree[p].maxPre = max(0, tree[p].sum), tree[p].cnt = (s[l] == 'A'), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, s), build(p << 1 | 1, mid + 1, r, s);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void reverse(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return upd(p, r - l + 1);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) reverse(p << 1, l, mid, ql, qr);
        if (qr > mid) reverse(p << 1 | 1, mid + 1, r, ql, qr);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }

   public:
    void build(string& s) { return build(1, 0, (n = (int)s.size()) - 1, s); }
    void reverse(int l, int r) { return reverse(1, 0, n - 1, l, r); }
    int query(void) { return tree[1].cnt - 1 - tree[1].minPre; }
} ST;

void solve(void) {
    int n, q;
    string s;
    cin >> n >> s >> q;
    s = "B" + s + "A";
    ST.build(s);
    while (q--) {
        int l, r;
        cin >> l >> r;
        ST.reverse(l + 1, r + 1);
        cout << ST.query() << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("medium.in", "r", stdin), freopen("medium.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
