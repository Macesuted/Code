/**
 * @file 4085.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-18
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

#define maxn 300005
#define mod 1000000007

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int Mod(int x) { return x >= mod ? x - mod : x; }

class Matrix {
   private:
    int a[3][3];

   public:
    Matrix(void) { memset(a, 0, sizeof(a)); }
    int* operator[](size_t x) { return a[x]; }
    int get(size_t x, size_t y) const { return a[x][y]; }
    void set(void) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) a[i][j] = (i == j);
        return;
    }
    Matrix T(void) const {
        Matrix ans;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) ans[j][i] = this->get(i, j);
        return ans;
    }
    Matrix operator+(const Matrix& o) const {
        Matrix ans;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) ans[i][j] = Mod(this->get(i, j) + o.get(i, j));
        return ans;
    }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++) ans[i][k] = (ans[i][k] + (int64_t)this->get(i, j) * o.get(j, k)) % mod;
        return ans;
    }
    Matrix operator^(int x) const {
        Matrix ans, a = *this;
        ans.set();
        while (x) {
            if (x & 1) ans = ans * a;
            a = a * a, x >>= 1;
        }
        return ans;
    }
};

Matrix lf, rf, linc, rinc, ldec, rdec, nul;

class SegmentTree {
   private:
    struct Node {
        Matrix ans, laz1, laz2;
    };

    Node tree[maxn << 2];
    int n;

    void update(int p, Matrix l, Matrix r) {
        return tree[p].ans = l * tree[p].ans * r, tree[p].laz1 = l * tree[p].laz1, tree[p].laz2 = tree[p].laz2 * r, void();
    }
    void pushDown(int p) {
        return update(p << 1, tree[p].laz1, tree[p].laz2), update(p << 1 | 1, tree[p].laz1, tree[p].laz2),
               tree[p].laz1 = tree[p].laz2 = nul, void();
    }
    void pushUp(int p) { return tree[p].ans = tree[p << 1].ans + tree[p << 1 | 1].ans, void(); }
    void build(int p, int l, int r, int a[]) {
        tree[p].laz1 = tree[p].laz2 = nul;
        if (l == r) return tree[p].ans = (linc ^ (a[l - 1] - 1)) * lf * rf * (rinc ^ (a[l + 1] - 3)), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, Matrix vl, Matrix vr) {
        if (ql <= l && r <= qr) return update(p, vl, vr);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, vl, vr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, vl, vr);
        return pushUp(p);
    }
    Matrix query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].ans;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 2, n - 1, a); }
    void update(int l, int r, Matrix vl, Matrix vr) { return update(1, 2, n - 1, max(2, l), min(n - 1, r), vl, vr); }
    int query(int l, int r) { return l <= r ? query(1, 2, n - 1, l, r)[0][0] : 0; }
} ST;

int a[maxn];

void solve(void) {
    int n, q, A, B;
    cin >> n >> q >> A >> B;
    for (int i = 1; i <= n; i++) cin >> a[i];
    nul.set();
    rf[0][0] = 2, rf[0][1] = rf[0][2] = 1;
    rinc[0][0] = rinc[0][1] = rinc[2][2] = 1, rinc[1][0] = A, rinc[2][0] = B;
    if (A)
        rdec[1][0] = rdec[2][2] = 1, rdec[0][1] = Inv(A), rdec[1][1] = Mod(mod - Inv(A)),
        rdec[2][1] = Mod(mod - B * Inv(A) % mod);
    else
        rdec[1][0] = rdec[1][1] = rdec[2][2] = 1, rdec[2][1] = Mod(mod - B);
    lf = rf.T(), linc = rinc.T(), ldec = rdec.T();
    ST.resize(n), ST.build(a);
    while (q--) {
        string op;
        int l, r;
        cin >> op >> l >> r;
        if (op == "plus")
            ST.update(l + 1, r + 1, linc, nul), ST.update(l - 1, r - 1, nul, rinc);
        else if (op == "minus")
            ST.update(l + 1, r + 1, ldec, nul), ST.update(l - 1, r - 1, nul, rdec);
        else
            cout << ST.query(l + 1, r - 1) << endl;
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