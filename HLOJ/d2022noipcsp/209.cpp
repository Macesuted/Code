/**
 * @file 209.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::putch;
using IO::read;
using IO::write;

bool mem1;

#define maxn 1000005
#define maxlgn 20

vector<int> graph[maxn];
int a[maxn], fa[maxn], dep[maxn], st[maxn], rk[maxn], dfn[maxn], son[maxn][maxlgn], cnt[maxn][maxlgn];
int64_t f[maxn][maxlgn];

int64_t getCnt(int l, int r, int p) { return cnt[r][p] - cnt[l][p]; }
int64_t calc(int p, int d) {
    int64_t ans = 0;
    int q = p;
    for (int i = maxlgn - 1; ~i; i--)
        if (d >> i & 1) q = son[q][i];
    for (int i = maxlgn - 1; ~i; i--)
        if (d >> i & 1) ans += f[p][i] + (getCnt(q, son[p][i], i) << i), p = son[p][i];
    return ans;
}

void solve(void) {
    int n = read();
    dep[1] = 1;
    for (int i = 1; i <= n; i++) a[i] = read(), st[i] = n;
    for (int i = 2; i <= n; i++) graph[fa[i] = read()].push_back(i), dep[i] = dep[fa[i]] + 1;
    queue<int> que;
    que.push(1);
    int dfnt = 0;
    while (!que.empty()) {
        int p = que.front();
        que.pop(), rk[dfn[p] = ++dfnt] = p, st[dep[p]] = min(st[dep[p]], dfnt);
        for (auto i : graph[p]) que.push(i);
    }
    for (int i = 1; i <= n; i++) {
        int p = rk[i];
        son[p][0] = (graph[p].empty() ? (dfn[p] == st[dep[p]] ? 0 : son[rk[i - 1]][0]) : graph[p].back());
    }
    for (int i = 1; i <= n; i++) {
        int p = rk[i];
        f[p][0] = a[p];
        for (int j = 0; j < maxlgn; j++) cnt[p][j] = ((a[p] >> j & 1) ? -1 : +1);
        if (st[dep[p]] != dfn[p]) {
            f[p][0] += f[rk[i - 1]][0];
            for (int j = 0; j < maxlgn; j++) cnt[p][j] += cnt[rk[i - 1]][j];
        }
    }
    for (int i = n; i; i--) {
        int p = rk[i];
        for (int j = 0; j < maxlgn; j++) cnt[p][j] += cnt[son[p][0]][j];
        for (int j = 1; j < maxlgn; j++)
            son[p][j] = son[son[p][j - 1]][j - 1],
            f[p][j] = f[p][j - 1] + f[son[p][j - 1]][j - 1] + (getCnt(son[p][j], son[p][j - 1], j - 1) << (j - 1));
    }
    int q = read();
    while (q--) {
        int x = read(), d = read() + 1;
        int64_t ans = calc(x, d);
        if (dfn[x] != st[dep[x]]) ans -= calc(rk[dfn[x] - 1], d);
        write(ans), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}