/**
 * @file game.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 1G
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
const int SIZE = (1 << 20) + 1;
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
void flush(void) {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
    return;
}
char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
template <class I>
I read(void) {
    I x;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = (x << 3) + (x << 1) + (c ^ 48);
    return x * f;
}
template <class I>
void write(I x) {
    if (!x) return putch('0');
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
using io::putch;
using io::read;
using io::write;

bool mem1;

#define maxn 305
#define maxm 90005
#define mod 998244353

int f[maxn], g[2][maxm];

vector<vector<int>> graph;

string s = " ";

long long Mod(long long x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        char c = getch();
        while (c != 'B' && c != 'W') c = getch();
        s.push_back(c);
    }
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y);
    }
    for (int i = n; i; i--)
        for (auto j : graph[i]) {
            if (s[i] == s[j])
                f[i] = max(f[i], f[j] + 1);
            else if (f[j] == 0)
                f[i] = max(f[i], 1);
        }
    g[0][0] = g[1][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = maxm - 1, t = (s[i] == 'B'); j >= f[i]; j--) g[t][j] = Mod(g[t][j] + g[t][j - f[i]]);
    long long ans = 0, sum = 0;
    for (int i = 0; i < maxm; i++) ans = Mod(ans + sum * g[0][i] % mod), sum = Mod(sum + g[1][i]);
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}