/**
 * @author Macesuted (macesuted@outlook.com)
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

#define maxn (1 << 20)

typedef pair<int, int> pii;

int m;
int dist[maxn], B1[105], B2[105], F1[105], F2[105], dis[105];
bool vis[maxn];

void Dijkstra(int start) {
    memset(vis, 0, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
    static priority_queue<pii, vector<pii>, greater<pii> > que;
    while (!que.empty()) que.pop();
    que.push((pii){dist[start] = 0, start});
    while (!que.empty()) {
        pii p = que.top();
        que.pop();
        if (vis[p.second]) continue;
        vis[p.second] = true;
        for (register int i = 1; i <= m; i++) {
            int S = p.second;
            if ((S & B1[i]) != B1[i] || (S & B2[i])) continue;
            int T = (S & ((maxn - 1) ^ F1[i])) | F2[i];
            if (dist[T] > dist[S] + dis[i]) que.push((pii){dist[T] = dist[S] + dis[i], T});
        }
    }
    return;
}

int main() {
    int n = read<int>(), maxS = (1 << n) - 1;
    m = read<int>();
    for (register int i = 1; i <= m; i++) {
        dis[i] = read<int>();
        string str = getstr();
        for (register int j = 0; j < n; j++)
            if (str[j] == '+')
                B1[i] |= 1 << j;
            else if (str[j] == '-')
                B2[i] |= 1 << j;
        str = getstr();
        for (register int j = 0; j < n; j++)
            if (str[j] == '-')
                F1[i] |= 1 << j;
            else if (str[j] == '+')
                F2[i] |= 1 << j;
    }
    Dijkstra(maxS);
    write(dist[0] == 0x3f3f3f3f ? 0 : dist[0]), putch('\n');
    return 0;
}