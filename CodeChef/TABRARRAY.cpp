/**
 * @file TABRARRAY.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-22
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

#define maxn 1005
#define maxsv 1000005
#define maxlgn 45
#define mod 998244353

bool notPrime[maxsv];
vector<int> prime;

vector<vector<int>> graph;

int f[maxn][maxlgn][maxlgn], g[maxlgn][maxlgn], h[maxlgn];

void dfs1(int p) {
    f[p][0][0] = 1;
    for (auto x : graph[p]) {
        dfs1(x);
        for (int i = 0; i < maxlgn; i++)
            for (int j = 0; j <= i; j++)
                g[i][j] = f[p][i][j];
        for (int i1 = 0; i1 < maxlgn; i1++)
            for (int j1 = 0; j1 <= i1; j1++)
                for (int i2 = 1; i1 + i2 < maxlgn; i2++)
                    for (int j2 = 0; j2 <= i2; j2++)
                        f[p][i1 + i2][max(j1, j2)] = (f[p][i1 + i2][max(j1, j2)] + 1LL * g[i1][j1] * f[x][i2][j2]) % mod;
    }
    for (int i = 0; i < maxlgn; i++)
        for (int j = 0; j <= i; j++)
            g[i][j] = f[p][i][j], f[p][i][j] = 0;
    for (int i = 0; i < maxlgn; i++)
        for (int j = 0; j <= i; j++)
            for (int k = j; p == 1 ? (k == j) : (j + k < maxlgn); k++)
                f[p][i + k][k] = (f[p][i + k][k] + g[i][j]) % mod;
    return;
}
int dfs2(vector<int>::iterator p, long long val, long long k, long long sum) {
    if (p == prime.end() || k / val < 1LL * *p * *p) return k / val % mod * sum % mod;
    long long ans = dfs2(p + 1, val, k, sum);
    val = val * *p;
    for (int i = 2; k / val >= *p; i++, val *= *p)
        ans = (ans + dfs2(p + 1, val * *p, k, sum * h[i] % mod)) % mod;
    return ans;
}

void solve(void) {
    int n = read<int>();
    long long k = read<long long>();
    graph.resize(n + 1);
    for (int i = 2; i <= n; i++) graph[read<int>()].push_back(i);
    dfs1(1);
    for (int i = 0; i < maxlgn; i++)
        for (int j = 0; j <= i; j++)
            h[i] = (h[i] + f[1][i][j]) % mod;
    write(dfs2(prime.begin(), 1, k, 1)), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    notPrime[1] = true;
    for (int i = 2; i < maxsv; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxsv; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
