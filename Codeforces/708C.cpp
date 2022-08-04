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
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 400005

vector<vector<int>> graph;

int siz[maxn], maxChild[maxn], limit;
bool answer[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = maxChild[p] = 1;
    for (auto i : graph[p]) {
        if (i == pre) continue;
        dfs1(i, p);
        siz[p] += siz[i], maxChild[p] = max(maxChild[p], maxChild[i]);
    }
    if (siz[p] <= limit) maxChild[p] = max(maxChild[p], siz[p]);
    return;
}
void dfs2(int p, int pre = -1) {
    answer[p] = true;
    for (auto i : graph[p])
        if (siz[i] > limit && siz[i] - maxChild[i] > limit) answer[p] = false;
    int maxChild1 = 1, maxChild2 = 1;
    for (auto i : graph[p])
        if (maxChild[i] > maxChild1)
            maxChild2 = maxChild1, maxChild1 = maxChild[i];
        else if (maxChild[i] > maxChild2)
            maxChild2 = maxChild[i];
    for (auto i : graph[p]) {
        if (i == pre) continue;
        int maxChild_p = maxChild[p], maxChild_i = maxChild[i];
        siz[p] -= siz[i], siz[i] += siz[p];
        maxChild[p] = (maxChild[i] == maxChild1 ? maxChild2 : maxChild1);
        if (siz[p] <= limit) maxChild[p] = max(maxChild[p], siz[p]);
        maxChild[i] = max(maxChild[i], maxChild[p]);
        dfs2(i, p);
        siz[i] -= siz[p], siz[p] += siz[i];
        maxChild[p] = maxChild_p, maxChild[i] = maxChild_i;
    }
    return;
}

int main() {
    int n = read<int>();
    limit = n / 2;
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), dfs2(1);
    for (register int i = 1; i <= n; i++) write((int)answer[i]), putch(" \n"[i == n]);
    return 0;
}