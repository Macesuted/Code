#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005
#define maxlgn 33
#define mod 998244353

inline int Mod(int x) { return x >= mod ? x - mod : x; }

class SegmentTree {
   private:
    int tree[maxn << 2][maxlgn], pos[maxn << 2], lazy[maxn << 2], n;

    void pushUp(int p) {
        for (int i = pos[p << 1], j = pos[p << 1 | 1], t = pos[p] = min(i, j); t < maxlgn; i++, j++, t++)
            tree[p][t] = Mod((i < maxlgn ? tree[p << 1][i] : 0) + (j < maxlgn ? tree[p << 1 | 1][j] : 0));
        return;
    }
    void pushDown(int p) {
        if (lazy[p] == 0) return;
        pos[p << 1] += lazy[p], pos[p << 1 | 1] += lazy[p];
        lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
        return;
    }
    void build(int p, int l, int r, int a[]) {
        pos[p] = lazy[p] = 0;
        if (l == r) {
            tree[p][0] = a[l];
            for (int i = 1; i < maxlgn; i++) tree[p][i] = (tree[p][i - 1] & (tree[p][i - 1] >> 1));
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return pos[p] += v, lazy[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int sum(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return pos[p] >= maxlgn ? 0 : tree[p][pos[p]];
        pushDown(p);
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = Mod(ans + sum(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = Mod(ans + sum(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void add(int l, int r, int v) { return add(1, 1, n, l, r, v); }
    int sum(int l, int r) { return sum(1, 1, n, l, r); }
} SGT;

typedef pair<int, int> pii;

int a[maxn];

stack<pii> S;

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    SGT.resize(n), SGT.build(a);
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
            SGT.add(l, r, +1);
            S.emplace(l, r);
        } else if (opt == 2) {
            int l, r;
            cin >> l >> r;
            cout << SGT.sum(l, r) << endl;
        } else {
            pii x = S.top();
            S.pop();
            SGT.add(x.first, x.second, -1);
        }
    }
    return 0;
}