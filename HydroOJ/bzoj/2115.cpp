/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
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
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 50005
#define maxlgn 63

typedef pair<int, long long> pii;

long long rec[maxlgn];

void insert(long long val) {
    for (register int i = maxlgn - 1; ~i; i--)
        if (val >> i & 1) {
            if (rec[i]) {
                val ^= rec[i];
                if (!val) return;
            } else {
                rec[i] = val;
                break;
            }
        }
    return;
}

vector<vector<pii> > graph;
bool vis[maxn];
int fa[maxn];
long long dist[maxn];

void dfs(int p, int pre) {
    fa[p] = pre, vis[p] = true;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (!vis[i->first])
            dist[i->first] = dist[p] ^ i->second, dfs(i->first, p);
        else if (i->first != pre)
            insert(dist[p] ^ dist[i->first] ^ i->second);
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i <= m; i++) {
        from = read<int>(), to = read<int>();
        long long dis = read<long long>();
        graph[from].push_back((pii){to, dis}), graph[to].push_back((pii){from, dis});
    }
    dfs(1, -1);
    long long answer = dist[n];
    for (register int i = maxlgn - 1; ~i; i--)
        if (!(answer >> i & 1) && rec[i]) answer ^= rec[i];
    write(answer), putch('\n');
    return 0;
}