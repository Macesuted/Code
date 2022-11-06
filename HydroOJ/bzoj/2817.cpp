/**
 * @file 2817.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int stack[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = x % 10, x /= 10;
    while (top) putch(stack[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    __int128 fx = x;
    for (int i = 0; i < dep; i++) stack[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        stack[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (stack[i] == 10) stack[i] = 0, stack[i - 1]++;
        if (stack[0] == 10) stack[0] = 0, fx++;
    }
    write(fx), x -= fx;
    if (!dep) return;
    putch('.');
    for (int i = 0; i < dep; i++) putch(stack[i] ^ 48);
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
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 105

namespace Solve1 {
__float128 f[2][maxn][maxn * maxn / 2][3];

void solve(int n, int m, int k) {
    int M = n * n / 2;
    f[0][0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bool t = i & 1;
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= M; k++)
                for (int l = 0; l < 3; l++) f[t][j][k][l] = 0;
        for (int j = 0; j < i; j++)
            for (int k = 0; k <= M; k++)
                for (int l = 0; l < 3; l++) {
                    if (f[!t][j][k][l] < 1e-10) continue;
                    int k_ = k + 2 * j - l;
                    f[t][j + 1][k_][l] += f[!t][j][k][l] * (j + 1 - l);
                    f[t][j][k_][l] += f[!t][j][k][l] * (2 * j - l);
                    if (j) f[t][j - 1][k_][l] += f[!t][j][k][l] * (j - 1);
                    if (l < 2)
                        f[t][j + 1][k_][l + 1] += f[!t][j][k][l] * (2 - l), f[t][j][k_][l + 1] += f[!t][j][k][l] * (2 - l);
                }
    }
    __float128 ans = 0;
    for (int i = m; i <= M; i++) ans += f[n & 1][1][i][2];
    for (int i = 1; i <= n; i++) ans /= i;
    writeDouble(ans, k);
    return;
}
}  // namespace Solve1
namespace Solve2 {
long double f[2][maxn][maxn * maxn / 2][3];

void solve(int n, int m, int k) {
    int M = n * n / 2;
    f[0][0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bool t = i & 1;
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= M; k++)
                for (int l = 0; l < 3; l++) f[t][j][k][l] = 0;
        for (int j = 0; j < i; j++)
            for (int k = 0; k <= M; k++)
                for (int l = 0; l < 3; l++) {
                    if (f[!t][j][k][l] < 1e-10) continue;
                    int k_ = k + 2 * j - l;
                    f[t][j + 1][k_][l] += f[!t][j][k][l] * (j + 1 - l);
                    f[t][j][k_][l] += f[!t][j][k][l] * (2 * j - l);
                    if (j) f[t][j - 1][k_][l] += f[!t][j][k][l] * (j - 1);
                    if (l < 2)
                        f[t][j + 1][k_][l + 1] += f[!t][j][k][l] * (2 - l), f[t][j][k_][l + 1] += f[!t][j][k][l] * (2 - l);
                }
    }
    long double ans = 0;
    for (int i = m; i <= M; i++) ans += f[n & 1][1][i][2];
    for (int i = 1; i <= n; i++) ans /= i;
    writeDouble(ans, k);
    return;
}
}  // namespace Solve2

void solve(void) {
    int n = read(), m = min(n * n / 2, read()), k = read();
    return k > 8 ? Solve1::solve(n, m, k) : Solve2::solve(n, m, k);
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