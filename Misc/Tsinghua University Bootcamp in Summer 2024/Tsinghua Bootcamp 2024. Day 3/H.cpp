#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define endl '\n'
#define maxn 200005

class SegmentTree {
   private:
    int maxv[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p) {
        if (!laz[p]) return;
        maxv[p << 1] += laz[p], laz[p << 1] += laz[p];
        maxv[p << 1 | 1] += laz[p], laz[p << 1 | 1] += laz[p];
        laz[p] = 0;
        return;
    }
    void pushUp(int p) { return maxv[p] = max(maxv[p << 1], maxv[p << 1 | 1]), void(); }
    void build(int p, int l, int r) {
        maxv[p] = laz[p] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return;
    }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return maxv[p] = v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return maxv[p] += v, laz[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return maxv[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }
    void print(int p, int l, int r) {
        if (l == r) return cerr << l << ' ' << maxv[p] << endl, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 0, n + 1); }
    void insert(int p, int v) { return insert(1, 0, n + 1, p, v); }
    void add(int l, int r, int v) { return add(1, 0, n + 1, l, r, v); }
    int query(int l, int r) { return l > r ? 0 : query(1, 0, n + 1, l, r); }
    void print(void) { return cerr << "PRINT" << endl, print(1, 0, n + 1); }
} ST, ST2;

int n;
int a[maxn], flu[maxn], fld[maxn], fru[maxn], frd[maxn];
vector<int> rec[maxn];

bool mem2;

int work(void) {
    flu[0] = fld[0] = flu[n + 1] = fld[n + 1] = 0;
    frd[0] = fru[n + 1] = 0;

    set<int> S;
    S.insert(n + 1);
    for (int i = 1; i <= n; i++) flu[a[i]] = flu[*next(S.insert(a[i]).first)] + 1;
    S.clear();
    S.insert(0);
    for (int i = 1; i <= n; i++) fld[a[i]] = fld[*prev(S.insert(a[i]).first)] + 1;
    S.clear();

    ST.resize(n), ST.build(), a[0] = 0;
    for (int i = n; ~i; i--) ST.insert(a[i], fru[a[i]] = ST.query(a[i] + 1, n) + 1);
    ST.build(), a[0] = n + 1;
    for (int i = n; ~i; i--) ST.insert(a[i], frd[a[i]] = ST.query(1, a[i]) + 1);
    fru[0]--, frd[n + 1]--;

    // for (int i = 1; i <= n; i++) cerr << a[i] << ' ';
    // cerr << endl;
    // for (int i = 1; i <= n; i++) cerr << frd[a[i]] << ' ';
    // cerr << endl;

    ST.build(), ST2.resize(n), ST2.build();

    for (int i = 0; i <= n; i++) rec[i].clear(), rec[i].push_back(n + 1);
    for (int i = n; i; i--) rec[frd[a[i]]].push_back(a[i]), ST2.insert(a[i], frd[a[i]]);

    S.insert(0), S.insert(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        rec[frd[a[i]]].pop_back();
        ST.add(a[i], rec[frd[a[i]]].back(), -1);

        // cerr << i << ' ' << ST.query(1, a[i]) << ' ' << fru[a[i]] << endl;
        ans = max(ans, ST.query(1, a[i]) + fru[a[i]]);

        ST2.insert(a[i], 0);

        auto p = S.insert(a[i]).first, pl = prev(p), pr = next(p);
        ST.insert(*p, flu[*p] + fld[*pl] + ST2.query(1, *p));
        ST.insert(*pr, flu[*pr] + fld[*p] + ST2.query(1, *pr));
    }
    return ans;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans1 = work();
    for (int i = 1; i <= n; i++) a[i] = n - a[i] + 1;
    int ans2 = work();

    cout << max(ans1, ans2) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    // cerr << abs(&mem1 - &mem2) / 1024. / 1024. << endl;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}