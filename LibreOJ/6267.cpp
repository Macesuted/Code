/**
 * @file 6267.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 1000005
#define maxm 10000005
#define mod 998244353

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
long long Mod(long long x, long long m = mod) { return x >= m ? x - m : x; }

int n, m, a[maxn];
bool vis[maxm], ins[maxm];
int val[maxm];
long long inv2, invm;

int calc(int p) {
    if (vis[p]) return val[p];
    static vector<int> S;
    S.clear(), S.push_back(p), vis[p] = ins[p] = true;
    for (int i = Mod(p + p, m); !vis[i]; i = Mod(i + i, m)) vis[i] = ins[i] = true, S.push_back(i);
    if (ins[Mod(S.back() + S.back(), m)]) {
        long long f = 1, d = 0;
        int p = Mod(S.back() + S.back(), m);
        auto i = S.begin();
        while (*i != p) i++;
        while (i != S.end()) d = (d + f * *i % mod * invm) % mod, f = f * inv2 % mod, i++;
        val[p] = d * Pow(Mod(1 + mod - f), mod - 2) % mod;
    }
    for (auto i = S.rbegin(); i != S.rend(); i++)
        val[*i] = (*i * invm + val[Mod(*i + *i, m)] * inv2) % mod, ins[*i] = false;
    return val[p];
}

void solve(void) {
    n = read<int>(), m = 0;
    for (int i = 1; i <= n; i++) m += (a[i] = read<int>());
    inv2 = Pow(2, mod - 2), invm = Pow(m, mod - 2);
    long long ans = 0;
    vis[0] = true, val[0] = 0;
    for (int i = 1; i <= n; i++) ans = Mod(ans + calc(a[i]));
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
