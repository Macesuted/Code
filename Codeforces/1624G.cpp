/**
 * @file 1624g.CPP
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

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
#define maxlgn 32

typedef tuple<int, int, int> tiii;

class UnionSet {
   private:
    int fa[maxn], n;
    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

   public:
    int cnt;

    void resize(int _n) {
        n = cnt = _n;
        for (int i = 1; i <= n; i++) fa[i] = i;
        return;
    }
    void merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return;
        fa[fx] = fy, cnt--;
        return;
    }
};

set<tiii> edges;

void solve(void) {
    int n = read<int>(), m = read<int>();
    edges.clear();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), d = read<int>();
        edges.emplace(x, y, d);
    }
    int ans = 0;
    for (int t = maxlgn - 1; ~t; t--) {
        UnionSet US;
        US.resize(n);
        for (auto i : edges)
            if (!(get<2>(i) >> t & 1)) US.merge(get<0>(i), get<1>(i));
        if (US.cnt == 1) {
            vector<tiii> cache;
            for (auto i : edges)
                if (get<2>(i) >> t & 1) cache.push_back(i);
            for (auto i : cache) edges.erase(i);
        } else
            ans ^= 1 << t;
    }
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
