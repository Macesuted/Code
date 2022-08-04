/**
 * @file 12717.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
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
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxlgn 62
#define mod 998244353

int64_t l[7], r[7], L[3], R[3], f[maxlgn][2][2][2];

int64_t& Plus(int64_t& a, int64_t x) { return a = (a + x >= mod ? a + x - mod : a + x); }

int64_t solve(int64_t R0, int64_t R1, int64_t R2) {
    if (R0 < 0 || R1 < 0 || R2 < 0) return 0;
    memset(f, 0, sizeof(f));
    f[maxlgn - 1][1][1][1] = 1;
    for (int i = maxlgn - 2; ~i; i--)
        for (int t0 = 0; t0 < 2; t0++)
            for (int t1 = 0; t1 < 2; t1++)
                for (int t2 = 0; t2 < 2; t2++) {
                    if (!f[i + 1][t0][t1][t2]) continue;
                    for (int b0 = 0, p0 = (R0 >> i & 1); b0 <= (t0 ? p0 : 1); b0++)
                        for (int b1 = 0, p1 = (R1 >> i & 1); b1 <= (t1 ? p1 : 1); b1++) {
                            int b2 = b0 ^ b1, p2 = (R2 >> i & 1);
                            if (t2 && b2 > p2) continue;
                            Plus(f[i][t0 && (b0 == p0)][t1 && (b1 == p1)][t2 && (b2 == p2)], f[i + 1][t0][t1][t2]);
                        }
                }
    int64_t ans = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) Plus(ans, f[0][i][j][k]);
    return ans;
}
void solve(void) {
    int64_t ans = 1;
    for (int i = 0; i < 7; i++)
        l[i] = read<int64_t>(), r[i] = read<int64_t>(), ans = ans * ((r[i] - l[i] + 1) % mod) % mod;
    L[0] = max({l[0], l[1], l[2]}) - 1, R[0] = min({r[0], r[1], r[2]});
    L[1] = l[3] - 1, R[1] = r[3];
    L[2] = max({l[4], l[5], l[6]}) - 1, R[2] = min({r[4], r[5], r[6]});
    if (L[0] > R[0] || L[1] > R[1] || L[2] > R[2]) return write(ans), putch('\n');
    write(
        ((ans - solve(R[0], R[1], R[2]) + solve(L[0], R[1], R[2]) + solve(R[0], L[1], R[2]) + solve(R[0], R[1], L[2]) -
          solve(L[0], L[1], R[2]) - solve(L[0], R[1], L[2]) - solve(R[0], L[1], L[2]) + solve(L[0], L[1], L[2])) %
             mod +
         mod) %
        mod),
        putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("qgygd.in", "r", stdin), freopen("qgygd.out", "w", stdout);
#endif
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