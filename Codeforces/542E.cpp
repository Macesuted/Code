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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
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

#define maxn 1005

vector<vector<int>> graph;
vector<int> vec;

int col[maxn], vis[maxn], tim = 0;

bool check(int p, int _col = 1) {
    if (col[p] && col[p] != _col) return false;
    if (col[p]) return true;
    vec.push_back(p);
    col[p] = _col;
    for (auto i : graph[p])
        if (!check(i, 3 - _col)) return false;
    return true;
}
int bfs(int p) {
    queue<int> que;
    que.push(p), vis[p] = tim;
    int cnt = -1;
    while (!que.empty()) {
        cnt++;
        queue<int> cache;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (vis[i] != tim) vis[i] = tim, cache.push(i);
        }
        que = cache;
    }
    return cnt;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (col[i]) continue;
        if (!check(i)) return putstr("-1\n"), 0;
        int tat = 0;
        for (auto j : vec) tim++, tat = max(tat, bfs(j));
        answer += tat;
        vec.clear();
    }
    write(answer), putch('\n');
    return 0;
}