/**
 * @file 1217F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

class UnionSet {
   private:
    int n, fa[maxn], siz[maxn];
    stack<pii> hist;

   public:
    void resize(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
        return;
    }
    int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
    void merge(int x, int y) {
        // cerr << "MERGE " << x << ' ' << y << endl;
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return hist.emplace(-1, -1);
        if (siz[fx] < siz[fy]) swap(fx, fy);
        hist.emplace(fx, fy), fa[fy] = fx, siz[fx] += siz[fy];
        return;
    }
    void rollBack(void) {
        int x, y;
        tie(x, y) = hist.top(), hist.pop();
        // cerr << "ROLL " << x << ' ' << y << endl;
        if (x == -1 && y == -1) return;
        fa[y] = y, siz[x] -= siz[y];
        return;
    }
} US;
pii a[maxn];
bool ask[maxn];
set<pii> stop[maxn];
map<pii, vector<int>> record;
int n, lastOpt;

pii sort(int x, int y) { return pii{min(x, y), max(x, y)}; }
pii decPii(pii a) { return sort(a.first == 1 ? n : a.first - 1, a.second == 1 ? n : a.second - 1); }
pii incPii(pii a) { return sort(a.first % n + 1, a.second % n + 1); }
pii thePii(pii a) { return lastOpt ? incPii(a) : a; }
int safe_upper_bound(vector<int>& vec, int n) {
    auto p = upper_bound(vec.begin(), vec.end(), n);
    return p == vec.end() ? 0x3f3f3f3f : *p;
}

class SegmentTree {
   private:
    int n, m;
    vector<pii> tree[maxn << 2];

    void insert(int p, int l, int r, int ql, int qr, pii edge) {
        if (ql <= l && r <= qr) return tree[p].push_back(edge);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, edge);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, edge);
        return;
    }
    void solve(int p, int l, int r) {
        // cerr << "#" << l << ' ' << r << endl;
        for (auto i : tree[p]) US.merge(i.first, i.second);
        if (l == r) {
            if (ask[l])
                write(lastOpt = (US.getfa(thePii(a[l]).first) == US.getfa(thePii(a[l]).second)));
            else {
                bool erase = false;
                for (auto i : stop[l])
                    if (i == thePii(a[l])) {
                        erase = true;
                        stop[l].erase(i);
                        break;
                    }
                if (!erase) stop[l].insert(thePii(a[l]));
                for (auto i : stop[l]) {
                    int nex = m;
                    if (record.find(i) != record.end()) nex = min(nex, safe_upper_bound(record[i], l));
                    if (record.find(decPii(i)) != record.end()) nex = min(nex, safe_upper_bound(record[decPii(i)], l));
                    if (nex != m) stop[nex].insert(i);
                    insert(l + 1, nex, i);
                }
                stop[l].clear();
            }
        } else {
            int mid = (l + r) >> 1;
            solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
        }
        for (auto i : tree[p]) US.rollBack();
        return;
    }
    void insert(int l, int r, pii opt) {
        // cerr << "INSERT " << l << ' ' << r << ' ' << opt.first << ' ' << opt.second << endl;
        return insert(1, 1, m, l, r, opt);
    }

   public:
    void resize(int _n, int _m) { return US.resize(n = _n), m = _m, void(); }
    void solve(void) { return solve(1, 1, m); }
};

SegmentTree SGT;

void solve(void) {
    n = read<int>();
    int m = read<int>();
    SGT.resize(n, m);
    for (int i = 1; i <= m; i++) {
        int t = read<int>(), x = read<int>(), y = read<int>();
        a[i] = sort(x, y);
        if (t == 1)
            record[a[i]].push_back(i);
        else
            ask[i] = true;
    }
    SGT.solve();
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
