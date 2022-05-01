/**
 * @file 36.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-23
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

#define maxn 100005
#define B 400

int v[maxn], f[B + 5][B + 5];

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) v[i] = read<int>();
    for (int i = 1; i <= B; i++)
        for (int j = 1; j <= n; j++) f[i][j % i] += v[j];
    cout << setiosflags(ios::fixed) << setprecision(4);
    while (m--)
        if (read<int>() == 1) {
            int x = read<int>(), y = read<int>();
            for (int i = 1; i <= B; i++) f[i][x % i] += y - v[x];
            v[x] = y;
        } else {
            int t = read<int>(), k = read<int>(), d = read<int>(), mt = n;
            double ans = 0;
            for (int i = 1; i <= t; i++) mt = min(mt, read<int>());
            if (t == 1) {
                if (d <= B)
                    ans = f[d][k % d];
                else
                    for (int i = k % d; i <= n; i += d) ans += v[i];
            } else {
                ans += v[k];
                double p = 1;
                for (int i = 1; i <= 60; i++) {
                    p *= 1. * (mt - i + 1) / (n - i);
                    if (k - i * d >= 1) ans += p * v[k - i * d];
                    if (k + i * d <= n) ans += p * v[k + i * d];
                }
            }
            cout << ans << endl;
        }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("lzz.in", "r", stdin), freopen("lzz.out", "w", stdout);
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
