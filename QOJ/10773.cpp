/**
 * @file 10773.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

class Matrix {
   private:
    vector<vector<int64_t>> a;

   public:
    void resize(int n, int m) { return a.resize(n, vector<int64_t>(m)); }

    vector<int64_t>& operator[](size_t x) { return a[x]; }
    const vector<int64_t>& operator[](size_t x) const { return a[x]; }

    friend Matrix operator+(const Matrix& a, const Matrix& b) {
        assert(a.a.size() == b.a.size() && a[0].size() == b[0].size());

        Matrix c;
        c.resize(a.a.size(), a[0].size());
        for (size_t i = 0; i < a.a.size(); i++)
            for (size_t j = 0; j < a[0].size(); j++) c[i][j] = a[i][j] + b[i][j];

        return c;
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        assert(a[0].size() == b.a.size());

        Matrix c;
        c.resize(a.a.size(), b[0].size());
        for (size_t i = 0; i < a.a.size(); i++)
            for (size_t j = 0; j < a[0].size(); j++)
                for (size_t k = 0; k < b[0].size(); k++) c[i][k] += a[i][j] * b[j][k];

        return c;
    }

    void setBase(size_t n) {
        a.clear(), a.resize(n, vector<int64_t>(n, 0));
        for (size_t i = 0; i < n; i++) a[i][i] = 1;
        return;
    }

    void print(void) const {
        for (const auto& l : a) {
            for (const auto& v : l) cerr << v << ' ';
            cerr << endl;
        }
        return;
    }
};

class SegmentTree {
   private:
    Matrix tree[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p) {
        tree[p << 1] = tree[p << 1] * laz[p], laz[p << 1] = laz[p << 1] * laz[p];
        tree[p << 1 | 1] = tree[p << 1 | 1] * laz[p], laz[p << 1 | 1] = laz[p << 1 | 1] * laz[p];
        laz[p].setBase(3);
        return;
    }
    void build(int p, int l, int r, Matrix a[]) {
        laz[p].setBase(3);
        if (l == r) return tree[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int ql, int qr, const Matrix& x) {
        if (ql <= l && r <= qr) return tree[p] = tree[p] * x, laz[p] = laz[p] * x, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, x);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, x);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Matrix query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(Matrix a[]) { return build(1, 1, n, a); }
    void update(int l, int r, const Matrix& x) { return update(1, 1, n, l, r, x); }
    Matrix query(int l, int r) { return query(1, 1, n, l, r); }
} SGT;

vector<int> graph[maxn];
int siz[maxn], dep[maxn], fa[maxn], top[maxn], son[maxn], dfni[maxn], dfno[maxn];
Matrix a[maxn], base[3][4];

void dfs1(int p, int pre = 0) {
    siz[p] = 1, dep[p] = dep[fa[p] = pre] + 1, son[p] = 0;
    for (auto q : graph[p])
        if (q != pre) {
            dfs1(q, p), siz[p] += siz[q];
            if (siz[q] > siz[son[p]]) son[p] = q;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int t) {
    dfni[p] = ++dfnt, top[p] = t;
    if (son[p]) dfs2(son[p], t);
    for (auto q : graph[p])
        if (q != fa[p] && q != son[p]) dfs2(q, q);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, Matrix>> rec;
    for (int i = 1, x, y, w; i < n; i++) {
        string d;
        cin >> x >> y >> w >> d;
        graph[x].push_back(y), graph[y].push_back(x);
        Matrix m;
        m.resize(1, 3), m[0][d[0] == 'x' ? 0 : d[0] == 'y' ? 1 : 2] = (d[1] == '+' ? +1 : -1) * w;
        rec.emplace_back(x, y, m);
    }

    dfs1(1), dfs2(1, 1);

    a[1].resize(1, 3);
    for (auto [x, y, m] : rec) {
        if (dep[x] > dep[y]) m[0][0] *= -1, m[0][1] *= -1, m[0][2] *= -1;
        a[max(dfni[x], dfni[y])] = m;
    }

    SGT.resize(n), SGT.build(a);

    base[0][0].setBase(3), base[1][0].setBase(3), base[2][0].setBase(3);
    base[0][1].resize(3, 3), base[0][1][0][0] = 1, base[0][1][1][2] = 1, base[0][1][2][1] = -1;
    base[1][1].resize(3, 3), base[1][1][0][2] = -1, base[1][1][1][1] = 1, base[1][1][2][0] = 1;
    base[2][1].resize(3, 3), base[2][1][0][1] = 1, base[2][1][1][0] = -1, base[2][1][2][2] = 1;

    for (int t = 0; t < 3; t++)
        for (int u = 2; u < 4; u++) base[t][u] = base[t][u - 1] * base[t][1];

    cout << setiosflags(ios::fixed) << setprecision(15);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            char cd;
            int d, w;
            cin >> cd >> w, d = (cd == 'x' ? 0 : cd == 'y' ? 1 : 2), w /= 90;
            if (dep[x] < dep[y])
                SGT.update(dfni[y], dfno[y], base[d][w]);
            else {
                SGT.update(2, n, base[d][w]);
                if (dfni[x] != dfno[x]) SGT.update(dfni[x] + 1, dfno[x], base[d][4 - w]);
            }
        } else {
            Matrix ans;
            ans.resize(1, 3);
            bool rev = true;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y), rev ^= true;
                Matrix m = SGT.query(dfni[top[x]], dfni[x]);
                if (rev) m[0][0] *= -1, m[0][1] *= -1, m[0][2] *= -1;
                ans = ans + m;
                x = fa[top[x]];
            }
            if (x != y) {
                if (dep[x] > dep[y]) swap(x, y), rev ^= true;
                Matrix m = SGT.query(dfni[x] + 1, dfni[y]);
                if (!rev) m[0][0] *= -1, m[0][1] *= -1, m[0][2] *= -1;
                ans = ans + m;
            }
            double x = ans[0][0], y = ans[0][1], z = ans[0][2];
            cout << sqrt(x * x + y * y + z * z) << endl;
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
