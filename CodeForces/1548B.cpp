/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

class SegmentTree {
   private:
    int tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        tree[p] = gcd(tree[p << 1], tree[p << 1 | 1]);
        return;
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = gcd(ans, query(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = gcd(ans, query(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void update(int p, int v) { return update(1, 1, n, p, v); }
    inline int query(int l, int r) { return query(1, 1, n, l, r); }
} tree;

int a[maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = n; i; i--) a[i] = abs(a[i] - a[i - 1]);
    tree.resize(n);
    for (register int i = 2; i <= n; i++) tree.update(i, a[i]);
    int answer = 0;
    for (register int l = 1, r = 1; r <= n; r++) {
        while (l < r && tree.query(l + 1, r) == 1) l++;
        answer = max(answer, r - l + 1);
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}