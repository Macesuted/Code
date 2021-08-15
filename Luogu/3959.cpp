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

long long f[maxn][maxS];
int record[maxn], dist[maxn][maxS];

vector<vector<pii> > graph;

int main() {
    int n = read<int>(), m = read<int>(), n2 = 1 << n;
    graph.resize(n);
    for (register int i = 1, from, to, dist; i <= m; i++) {
        from = read<int>() - 1, to = read<int>() - 1, dist = read<int>();
        graph[from].push_back((pii){to, dist}), graph[to].push_back((pii){from, dist});
    }
    for (register int i = 0; i < n; i++) {
        memset(record, 0x3f, sizeof(record));
        for (vector<pii>::iterator j = graph[i].begin(); j != graph[i].end(); j++)
            record[j->first] = min(record[j->first], j->second);
        for (register int j = 0; j < n2; j++) {
            dist[i][j] = 0x3f3f3f3f;
            for (register int k = 0; k < n; k++)
                if (j >> k & 1) dist[i][j] = min(dist[i][j], record[k]);
        }
    }
    memset(f, 0x3f, sizeof(f));
    for (register int i = 0; i < n; i++) f[0][1 << i] = 0;
    for (register int i = 1; i < n; i++)
        for (register int j = 1; j < n2; j++)
            for (register int k = (j - 1) & j; k; k = (k - 1) & j) {
                long long cost = 0;
                for (register int t = 0; t < n; t++)
                    if ((j >> t & 1) && !(k >> t & 1))
                        cost += dist[t][k];
                f[i][j] = min(f[i][j], f[i - 1][k] + cost * i);
            }
    long long answer = 0x3f3f3f3f3f3f3f3f;
    for (register int i = 0; i < n; i++) answer = min(answer, f[i][n2 - 1]);
    write(answer), putch('\n');
    return 0;
}