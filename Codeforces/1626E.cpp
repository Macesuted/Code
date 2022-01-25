/**
 * @file 1626E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
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

bool mem1;

#define maxn 300005

typedef pair<int, bool> pib;

int c[maxn], siz[maxn];
bool ans[maxn];

vector<vector<pib>> graph;

int cntb;

bool dfs(int p, int pre = -1) {
    siz[p] = c[p];
    for (auto& i : graph[p])
        if (i.first != pre) {
            i.second = dfs(i.first, p);
            if (siz[i.first] == 1) {
                for (auto& i : graph[i.first])
                    if (i.first == p) i.second = true;
            }
            siz[p] += siz[i.first];
        }
    if (cntb - siz[p] == 1) return true;
    return false;
}

void solve(void) {
    int n = read<int>();
    graph.resize(n + 1);
    cntb = 0;
    for (int i = 1; i <= n; i++) cntb += (c[i] = read<int>());
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].emplace_back(y, false), graph[y].emplace_back(x, false);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) ans[i] = false;
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (c[i]) {
            ans[i] = true;
            for (auto j : graph[i])
                if (!ans[j.first])
                    ans[j.first] = true, que.push(j.first);
        }
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (!i.second && !ans[i.first])
                ans[i.first] = true, que.push(i.first);
    }
    for (int i = 1; i <= n; i++) write((int)ans[i]), putch(" \n"[i == n]);
    graph.clear();
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
