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

vector<vector<int> > graph;
set<pii> S;
int dist[maxn];

pii dfs(int p, int pre) {
    pii answer = (pii){0, p};
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            pii ret = dfs(*i, p);
            ret.first += S.find((pii){p, *i}) != S.end() ? -1 : 1;
            if (ret.first > answer.first) answer = ret;
        }
    return answer;
}
bool dfs2(int p, int pre, int to) {
    if (p == to) return true;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre && dfs2(*i, p, to)) return S.insert((pii){p, *i}), S.insert((pii){*i, p}), true;
    return false;
}
int dfs3(int p, int pre) {
    int answer = 0;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            answer = max(answer, dfs3(*i, p));
            int dis = S.find((pii){p, *i}) != S.end() ? -1 : 1;
            answer = max(answer, dist[*i] + dis + dist[p]);
            dist[p] = max(dist[p], dist[*i] + dis);
        }
    return answer;
}

int main() {
    int n = read<int>(), k = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i < n; i++) {
        from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    int p1 = dfs(1, -1).second;
    pii ret = dfs(p1, -1);
    int answer = (n - 1) * 2 - ret.first + 1, p2 = ret.second;
    if (k == 1) {
        write(answer), putch('\n');
        return 0;
    }
    dfs2(p1, -1, p2);
    answer = answer - dfs3(1, -1) + 1;
    write(answer), putch('\n');
    return 0;
}