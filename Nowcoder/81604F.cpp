/**
 * @file 81604F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::putch;
using IO::read;
using IO::write;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
#define maxlgn 21

typedef pair<int, int64_t> pil;
typedef tuple<int, int, int, int64_t> tiiil;

class SegmentTree {
   private:
    struct Node {
        int maxv, minv, llen, len;
        int64_t lsum, sum, laz;
        Node(void) { minv = INT_MAX, maxv = llen = len = lsum = sum = laz = 0; }
    };

    Node tree[1 << 21];
    int n;

    void pushDown(int p) {
        if (!tree[p].laz) return;
        tree[p << 1].sum += tree[p << 1].len * tree[p].laz, tree[p << 1 | 1].sum += tree[p << 1 | 1].len * tree[p].laz;
        tree[p << 1].lsum += tree[p << 1].llen * tree[p].laz, tree[p << 1 | 1].lsum += tree[p << 1 | 1].llen * tree[p].laz;
        tree[p << 1].laz += tree[p].laz, tree[p << 1 | 1].laz += tree[p].laz, tree[p].laz = 0;
        return;
    }
    tiiil find(int p, int l, int r, int limit) {
        if (tree[p].minv >= limit) return {INT_MAX, 0, 0, 0};
        if (tree[p].maxv < limit) return {tree[p].minv, tree[p].maxv, tree[p].len, tree[p].sum};
        pushDown(p);
        int mid = (l + r) >> 1;
        if (tree[p << 1 | 1].minv >= limit) return find(p << 1, l, mid, limit);
        tiiil ret = find(p << 1 | 1, mid + 1, r, limit);
        return {tree[p].minv, get<1>(ret), tree[p].llen + get<2>(ret), tree[p].lsum + get<3>(ret)};
    }
    void build(int p, int l, int r, int dep[]) {
        if (l == r) return tree[p].maxv = tree[p].minv = dep[l], tree[p].len = 1, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, dep), build(p << 1 | 1, mid + 1, r, dep);
        tiiil ret = find(p << 1, l, mid, tree[p << 1 | 1].minv);
        tree[p].minv = min(get<0>(ret), tree[p << 1 | 1].minv), tree[p].maxv = tree[p << 1 | 1].maxv;
        tree[p].len = (tree[p].llen = get<2>(ret)) + tree[p << 1 | 1].len;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int64_t v, int& vl, int& vr) {
        if (ql <= l && r <= qr)
            return tree[p].sum += tree[p].len * v, tree[p].lsum += tree[p].llen * v, tree[p].laz += v, vl = 1, vr = tree[p].len,
                                                                                                       void();
        int mid = (l + r) >> 1, pl, pr;
        vl = n, vr = 1;
        pushDown(p);
        if (ql <= mid) {
            update(p << 1, l, mid, ql, qr, v, pl, pr), pr = min(pr, tree[p].llen);
            if (pl <= pr)
                tree[p].sum += (pr - pl + 1) * v, tree[p].lsum += (pr - pl + 1) * v, vl = min(vl, pl), vr = max(vl, pr);
        }
        if (qr > mid) {
            update(p << 1 | 1, mid + 1, r, ql, qr, v, pl, pr), pl += tree[p].llen, pr += tree[p].llen;
            if (pl <= pr) tree[p].sum += (pr - pl + 1) * v, vl = min(vl, pl), vr = max(vr, pr);
        }
        return;
    }
    pil query(int p, int l, int r, int qr) {
        if (r <= qr) return {tree[p].minv, tree[p].sum};
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, qr);
        pil rig = query(p << 1 | 1, mid + 1, r, qr);
        tiiil lef = find(p << 1, l, mid, rig.first);
        return {min(get<0>(lef), rig.first), get<3>(lef) + rig.second};
    }
    void print(int p, int l, int r) {
        cerr << "# " << p << ' ' << l << ' ' << r << endl;
        cerr << tree[p].minv << ' ' << tree[p].maxv << ' ' << tree[p].len << ' ' << tree[p].sum << ' ' << tree[p].llen << ' '
             << tree[p].lsum << endl;
        if (l == r) return;
        pushDown(p);
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int dep[]) { return build(1, 1, n, dep); }
    void update(int l, int r, int64_t v) {
        int pl, pr;
        return update(1, 1, n, l, r, v, pl, pr);
    }
    int64_t query(int r) { return query(1, 1, n, r).second; }
    void print(void) { return print(1, 1, n); }
} ST;

int dep[maxn], fa[maxn][maxlgn];

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

void solve(void) {
    int n = read(), q = read();

    fa[1][0] = 1, dep[1] = 1;
    for (int i = 2; i <= n; i++) fa[i][0] = read(), dep[i] = dep[fa[i][0]] + 1;

    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j <= n; j++) fa[j][i] = fa[fa[j][i - 1]][i - 1];

    ST.resize(n), ST.build(dep);

    int64_t lastans = 0;
    while (q--)
        if (read() == 1) {
            int64_t l = read<int64_t>() ^ lastans, r = read<int64_t>() ^ lastans, v = read<int64_t>() ^ lastans;
            l = l % n + 1, r = r % n + 1, v = v % n + 1;
            ST.update(l, r, v);
        } else {
            int64_t x = read<int64_t>() ^ lastans, y = read<int64_t>() ^ lastans;
            x = x % n + 1, y = y % n + 1;
            int t = lca(x, y);
            int64_t ans = ST.query(x) + ST.query(y) - ST.query(t);
            if (t != 1) ans -= ST.query(fa[t][0]);
            write(ans), putch('\n'), lastans ^= ans;
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