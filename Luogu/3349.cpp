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

#define maxn 18

bool graph[maxn][maxn];
int cnt[1 << maxn];
long long f[maxn][maxn];
vector<vector<int> > tree;
int n;

void dfs(int p, int S, int fa = -1) {
    for (vector<int>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        if (*i != fa) dfs(*i, S, p);
    for (register int i = 0; i < n; i++) {
        if (!(S >> i & 1)) continue;
        f[p][i] = 1;
        for (vector<int>::iterator j = tree[p].begin(); j != tree[p].end(); j++) {
            if (*j == fa) continue;
            long long sum = 0;
            for (register int k = 0; k < n; k++)
                if ((S >> k & 1) && graph[i + 1][k + 1]) sum += f[*j][k];
            f[p][i] *= sum;
        }
    }
    return;
}

int main() {
    n = read<int>();
    int m = read<int>();
    tree.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>();
        graph[from][to] = graph[to][from] = true;
    }
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>();
        tree[from].push_back(to), tree[to].push_back(from);
    }
    long long answer = 0;
    for (register int S = 0; S < (1 << n); S++) {
        dfs(1, S);
        long long sum = 0;
        for (register int i = 0; i < n; i++)
            if (S >> i & 1) sum += f[1][i];
        cnt[S] = cnt[S >> 1] + (S & 1);
        answer += (((n - cnt[S]) & 1) ? -1 : 1) * sum;
    }
    write(answer), putch('\n');
    return 0;
}