/**
 * @file 3299.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 22)
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

#define maxn 2000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    pii tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, pii v) {
        if (l == r) return tree[p].first += v.first, tree[p].second += v.second, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        tree[p].first = tree[p << 1].first + tree[p << 1 | 1].first;
        tree[p].second = tree[p << 1].second + tree[p << 1 | 1].second;
        return;
    }
    pii query1(int p, int l, int r, pii pre = {0, 0}) {
        if (l == r) return {min(pre.first + tree[p].first, pre.second + tree[p].second), p};
        int mid = (l + r) >> 1;
        pii ppre = {pre.first + tree[p << 1].first, pre.second + tree[p << 1].second};
        if (ppre.first > ppre.second) return query1(p << 1, l, mid, pre);
        return max(pii{min(ppre.first, ppre.second), mid}, query1(p << 1 | 1, mid + 1, r, ppre));
    }
    pii query2(int p, int l, int r, pii pre = {0, 0}) {
        if (l == r) return {min(pre.first + tree[p].first, pre.second + tree[p].second), p};
        int mid = (l + r) >> 1;
        pii ppre = {pre.first + tree[p << 1].first, pre.second + tree[p << 1].second};
        if (ppre.first < ppre.second) return query2(p << 1 | 1, mid + 1, r, ppre);
        return query2(p << 1, l, mid, pre);
    }
    int query3(int p, int l, int r, int lim, int pre = 0) {
        if (l == r) return pre + tree[p].second >= lim ? l : 0;
        int mid = (l + r) >> 1;
        if (pre + tree[p << 1].second < lim) return query3(p << 1, l, mid, lim, pre);
        return max(mid, query3(p << 1 | 1, mid + 1, r, lim, pre + tree[p << 1].second));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, pii v) { return update(1, 1, n, p, v); }
    pii query(void) {
        int ans = max(query1(1, 1, n).first, query2(1, 1, n).first);
        return {ans, query3(1, 1, n, ans)};
    }
} ST;

struct {
    int opt, type, x, y;
} a[maxn];
int t[maxn];

void solve(void) {
    int n = read<int>(), tcnt = 0;
    for (int i = 1; i <= n; i++) {
        a[i].opt = read<int>();
        if (a[i].opt == 1)
            a[i].type = read<int>(), t[++tcnt] = a[i].x = read<int>(), a[i].y = read<int>();
        else
            a[i].x = read<int>();
    }
    sort(t + 1, t + tcnt + 1), tcnt = unique(t + 1, t + tcnt + 1) - t - 1;
    for (int i = 1; i <= n; i++)
        if (a[i].opt == 1) a[i].x = lower_bound(t + 1, t + tcnt + 1, a[i].x) - t;
    ST.resize(tcnt);
    for (int i = 1; i <= n; i++) {
        if (a[i].opt == 1)
            if (a[i].type == 0)
                ST.update(a[i].x, {a[i].y, 0});
            else
                ST.update(1, {0, a[i].y}), a[i].x == tcnt ? void() : ST.update(a[i].x + 1, {0, -a[i].y});
        else if (a[a[i].x].type == 0)
            ST.update(a[a[i].x].x, {-a[a[i].x].y, 0});
        else
            ST.update(1, {0, -a[a[i].x].y}), a[a[i].x].x == tcnt ? void() : ST.update(a[a[i].x].x + 1, {0, a[a[i].x].y});
        pii ret = ST.query();
        if (ret.first == 0)
            putstr("Peace\n");
        else
            write(t[ret.second]), putch(' '), write(ret.first * 2), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
