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

#define maxn 200005
#define mod 10007

vector<vector<int> > graph;
int a[maxn];

int main() {
//    freopen("link.in", "r", stdin), freopen("link.out", "w", stdout);
    int n = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int ans1 = 0, ans2 = 0;
    for (register int i = 1; i <= n; i++) {
        if ((int)graph[i].size() < 2) continue;
        int max1 = 0, max2 = 0, sum = 0;
        for (vector<int>::iterator j = graph[i].begin(); j != graph[i].end(); j++) {
            sum = (sum + a[*j]) % mod;
            if (a[*j] > max1)
                max2 = max1, max1 = a[*j];
            else if (a[*j] > max2)
                max2 = a[*j];
        }
        ans1 = max(ans1, max1 * max2);
        for (vector<int>::iterator j = graph[i].begin(); j != graph[i].end(); j++) ans2 = (ans2 + a[*j] * (sum - a[*j])) % mod;
    }
    write(ans1), putch(' '), write((ans2 + mod) % mod), putch('\n');
    return 0;
}
