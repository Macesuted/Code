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

#define maxn 100005

typedef pair<int, int> pii;

vector<vector<pii> > graph;
int vis[maxn], cnt[5];
bool fail;

inline int color(int p) { return p < 1 ? p + 3 : (p > 3 ? p - 3 : p); }

void dfs(int p, int col = 1) {
    cnt[vis[p] = col]++, cnt[4]++;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
        if (i->second == 1) cnt[0]++;
        if (!vis[i->first])
            dfs(i->first, color(col + i->second));
        else if (vis[i->first] != color(col + i->second))
            fail = true;
    }
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].push_back((pii){to, 1}), graph[to].push_back((pii){from, -1});
    }
    long long answer = 0;
    for (register int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        cnt[0] = cnt[1] = cnt[2] = cnt[3] = cnt[4] = 0, fail = false;
        dfs(i);
        if (fail)
            answer += 1LL * cnt[4] * cnt[4];
        else if (cnt[1] && cnt[2] && cnt[3])
            answer += 1LL * cnt[1] * cnt[2] + 1LL * cnt[2] * cnt[3] + 1LL * cnt[3] * cnt[1];
        else
            answer += cnt[0];
    }
    write(answer), putch('\n');
    return 0;
}