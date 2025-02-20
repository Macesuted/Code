/**
 * @file 6952.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

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

#define maxn 250005
#define maxsqrtn 600
#define mod 998244353

typedef pair<int, int> pii;

bool notp[maxn];
vector<int> prime;
set<int> S[maxn];
int64_t a[maxn], mul[maxsqrtn], f[maxn], nxt[maxn];
int xv[maxn], bl[maxsqrtn], br[maxsqrtn], bel[maxn], rest[maxn], jmp[maxn];
bool vis[maxsqrtn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

vector<int> split(int v) {
    vector<int> ans;
    while (v != 1) ans.push_back(xv[v]), v /= xv[v];
    return ans;
}

void build(int id) {
    for (int i = br[id]; i >= bl[id]; i--) {
        f[i] = a[i], nxt[i] = i + jmp[i];
        if (nxt[i] <= br[id]) f[i] = Mod(f[i] + f[nxt[i]]), nxt[i] = nxt[nxt[i]];
    }
    return;
}

void solve(void) {
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read(), rest[i] = i / (jmp[i] = __gcd((int64_t)i, a[i]));
        auto ret = split(rest[i]);
        for (auto v : ret) S[v].insert(i);
    }

    int Bsiz = sqrt(n), Bcnt = 0;
    while (br[Bcnt] < n) Bcnt++, bl[Bcnt] = br[Bcnt - 1] + 1, br[Bcnt] = min(br[Bcnt - 1] + Bsiz, n), mul[Bcnt] = 1;

    for (int t = 1; t <= Bcnt; t++)
        for (int i = bl[t]; i <= br[t]; i++) bel[i] = t;

    for (int t = 1; t <= Bcnt; t++) build(t);

    while (q--) {
        int op = read();
        if (op == 1) {
            int l = read(), r = read(), x = read();
            vector<int> rec;

            rec.push_back(bel[l]), rec.push_back(bel[r]);

            if (bel[l] == bel[r])
                for (int i = l; i <= r; i++) a[i] = a[i] * x % mod;
            else {
                for (int i = l; i <= br[bel[l]]; i++) a[i] = a[i] * x % mod;
                for (int i = bl[bel[r]]; i <= r; i++) a[i] = a[i] * x % mod;
                for (int i = bel[l] + 1; i < bel[r]; i++) mul[i] = mul[i] * x % mod;
            }

            vector<int> ret = split(x);
            for (auto v : ret)
                for (auto p = S[v].lower_bound(l); p != S[v].end() && *p <= r;) {
                    rec.push_back(bel[*p]), rest[*p] /= v, jmp[*p] *= v;
                    if (rest[*p] % v)
                        p = S[v].erase(p);
                    else
                        p++;
                }

            for (auto id : rec)
                if (!vis[id]) vis[id] = true, build(id);
            for (auto id : rec) vis[id] = false;
        } else {
            int x = read();
            int64_t ans = 0;
            while (x <= n) ans = (ans + f[x] * mul[bel[x]]) % mod, x = nxt[x];
            write(ans), putch('\n');
        }
    }

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) {
        if (!notp[i]) prime.push_back(i), xv[i] = i;
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            notp[i * *j] = true, xv[i * *j] = *j;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}