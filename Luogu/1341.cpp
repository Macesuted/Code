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

#define maxV 128

typedef pair<int, int> pii;

vector<set<int> > graph;

stack<char> S;

int deg[maxV];
bool vis[maxV];

void dfs(int p) {
    vis[p] = true;
    while (!graph[p].empty()) {
        int to = *graph[p].begin();
        graph[p].erase(graph[p].begin());
        graph[to].erase(p);
        dfs(to);
    }
    S.push(p);
    vis[p] = false;
    return;
}

int main() {
    int n = read<int>();
    graph.resize(maxV);
    for (register int i = 1; i <= n; i++) {
        char c1 = getch();
        while (c1 == ' ' || c1 == '\r' || c1 == '\n') c1 = getch();
        char c2 = getch();
        graph[c1].insert(c2), graph[c2].insert(c1);
        deg[c1]++, deg[c2]++;
    }
    int cnt = 0;
    for (register int i = 0; i < maxV; i++)
        if (deg[i] & 1) cnt++;
    if (cnt != 0 && cnt != 2) return putstr("No Solution\n"), 0;
    if (cnt == 0) {
        for (register int i = 0; i < maxV; i++)
            if (deg[i]) {
                dfs(i);
                break;
            }
    } else {
        for (register int i = 0; i < maxV; i++)
            if (deg[i] & 1) {
                dfs(i);
                break;
            }
    }
    while (!S.empty()) putch(S.top()), S.pop();
    putch('\n');
    return 0;
}