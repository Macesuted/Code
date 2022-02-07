/**
 * @file 1632E2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-07
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

vector<vector<int>> graph;
int f[maxn];  // f[i] 表示层数 > i 的所有结点中最远的两个结点之间的距离

int dfs(int p, int pre = -1, int dep = 0) {
    int d1 = dep, d2 = dep;
    for (auto i : graph[p])
        if (i != pre) {
            int d = dfs(i, p, dep + 1);
            if (d > d1)
                d2 = d1, d1 = d;
            else if (d > d2)
                d2 = d;
        }
    int lim = d2 - 1;
    if (~lim) f[lim] = max(f[lim], d1 + d2 - 2 * dep);
    return d1;
}

void solve(void) {
    int n = read<int>();
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) {
        x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    for (int i = 0; i <= n; i++) f[i] = 0;
    int maxDep = dfs(1);
    for (int i = n - 1; ~i; i--) f[i] = max(f[i], f[i + 1]);
    for (int i = 1, ans = 0; i <= n; i++) {
        while (min(maxDep, (f[ans] + 1) / 2 + i) > ans) ans++;
        write(ans), putch(" \n"[i == n]);
    }
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
