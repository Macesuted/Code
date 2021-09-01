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

#define maxn 2005

typedef pair<int, int> pii;

vector<vector<int> > graph;

int indeg[maxn], deg[maxn], k[maxn], cnt[maxn];
bool vis[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) k[i] = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>();
        graph[to].push_back(from), indeg[from]++;
    }
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (register int i = 1; i <= n; i++)
        if ((deg[i] = indeg[i]) == 0) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
            k[*i] = min(k[*i], k[p] - 1);
            if (!--deg[*i]) que.push(*i);
        }
    }
    static vector<pii> cache;
    cache.clear();
    for (register int i = 1; i <= n; i++) cache.push_back((pii){k[i], i});
    sort(cache.begin(), cache.end());
    for (vector<pii>::iterator i = cache.begin(); i != cache.end(); i++) write(i->second), putch(' ');
    putch('\n');
    for (register int t = 1; t <= n; t++) {
        memset(vis, 0, sizeof(vis)), memset(cnt, 0, sizeof(cnt));
        que.push(t), vis[t] = true;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (!vis[*i]) que.push(*i), vis[*i] = true;
        }
        for (register int i = 1; i <= n; i++)
            if (!vis[i]) cnt[k[i]]++;
        for (register int i = n; i; i--)
            if ((cnt[i] += cnt[i + 1]) < n - i + 1) {
                write(i), putch(' ');
                break;
            }
    }
    putch('\n');
    return 0;
}