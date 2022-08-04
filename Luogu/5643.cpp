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

#define maxn 19
#define mod 998244353

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}
inline long long inv(long long x) { return power(x, mod - 2); }

vector<vector<int> > graph;
long long A[maxn], B[maxn], cnt[1 << maxn], f[1 << maxn];
int n;

void dfs(int p, int S, int fa = -1) {
    if (S >> (p - 1) & 1) return;
    long long sumA = 0, sumB = 0;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa) dfs(*i, S, p), sumA = (sumA + A[*i]) % mod, sumB = (sumB + B[*i]) % mod;
    A[p] = inv(((long long)graph[p].size() - sumA + mod) % mod);
    B[p] = (long long)(sumB + graph[p].size()) * A[p] % mod;
    return;
}

int main() {
    n = read<int>();
    int q = read<int>(), root = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    for (register int i = 1; i < (1 << n); i++) cnt[i] = cnt[i >> 1] + (i & 1);
    for (register int S = 1; S < (1 << n); S++) {
        for (register int i = 1; i <= n; i++) A[i] = B[i] = 0;
        dfs(root, S);
        f[S] = (((cnt[S] & 1) ? 1 : -1) * B[root] + mod) % mod;
    }
    for (register int i = 1; i < (1 << n); i <<= 1)
        for (register int j = 0; j < (1 << n); j += (i << 1))
            for (register int k = 0; k < i; k++) f[i + j + k] = (f[i + j + k] + f[j + k]) % mod;
    while (q--) {
        int k = read<int>(), S = 0;
        for (register int i = 1; i <= k; i++) S |= 1 << (read<int>() - 1);
        write((f[S] + mod) % mod), putch('\n');
    }
    return 0;
}