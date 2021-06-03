/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
inline void putch(char x) {
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
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    register T x = t;
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

#define maxn 13
#define maxS (1 << maxn)

typedef pair<int, int> pii;

struct LCA {
    int lca, x, y;
};

long long f[maxn][maxS];
int n, m, q;
vector<pii> edges;
vector<LCA> lca;

long long F(int p, int S) {
    if (~f[p][S]) return f[p][S];
    S ^= 1 << p;
    int sp = 0;
    while (!(S >> sp & 1)) sp++;
    f[p][S ^ (1 << p)] = 0;
    for (register int i = S; i; i = (i - 1) & S) {
        if (!(i >> sp & 1)) continue;
        bool pass = false;
        for (vector<LCA>::iterator j = lca.begin(); j != lca.end(); j++)
            if (j->lca == p && (i >> j->x & 1) && (i >> j->y & 1)) pass = true;
        if (pass) continue;
        for (vector<LCA>::iterator j = lca.begin(); j != lca.end(); j++)
            if ((i >> j->lca & 1) && (!(i >> j->x & 1) || !(i >> j->y & 1))) pass = true;
        if (pass) continue;
        for (vector<pii>::iterator j = edges.begin(); j != edges.end(); j++)
            if (j->first != p && j->second != p && ((i >> j->first & 1) ^ (i >> j->second & 1))) pass = true;
        if (pass) continue;
        bool choose = false;
        int ppp = 0;
        for (vector<pii>::iterator j = edges.begin(); j != edges.end(); j++)
            if (j->first == p && (i >> j->second & 1))
                choose ? pass = true : (choose = true, ppp = j->second);
            else if (j->second == p && (i >> j->first & 1))
                choose ? pass = true : (choose = true, ppp = j->first);
        if (pass) continue;
        if (choose)
            f[p][S ^ (1 << p)] += F(ppp, i) * F(p, S ^ i ^ (1 << p));
        else
            for (register int j = 0; j < n; j++)
                if (i >> j & 1) f[p][S ^ (1 << p)] += F(j, i) * F(p, S ^ i ^ (1 << p));
    }
    return f[p][S ^ (1 << p)];
}

int main() {
    memset(f, -1, sizeof(f));
    n = read<int>(), m = read<int>(), q = read<int>();
    while (m--) edges.push_back((pii){read<int>() - 1, read<int>() - 1});
    while (q--) {
        int a = read<int>() - 1, b = read<int>() - 1, c = read<int>() - 1;
        lca.push_back((LCA){c, a, b});
    }
    for (register int i = 0; i < n; i++) f[i][1 << i] = 1;
    write(F(0, (1 << n) - 1)), putch('\n');
    return 0;
}