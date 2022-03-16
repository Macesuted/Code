/**
 * @file 6813.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-16
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
#define maxp 505

int p[maxn], q[maxn];
double f[maxn], g[maxn][2], h[2][maxp][maxp * 2];

void solve(void) {
    int n = read<int>();
    for (int i = 0; i < n; i++) p[i] = read<int>();
    for (int i = 0; i < n; i++) q[i] = read<int>();
    for (int i = 1; i < maxp; i++)
        for (int j = 0; j < maxp * 2; j++) {
            for (int k = 1; k <= i; k++) h[0][i][j] += max(j - k, 0), h[1][i][j] += min(j + 1, k);
            h[0][i][j] /= i * (j + 1), h[1][i][j] /= i * (j + 1);
        }
    f[n] = g[n][0] = g[n][1] = 0;
    for (int i = n - 1; ~i; i--) {
        g[i][0] = 1, g[i][1] = 0;
        for (int j = i + 1; j <= min(n, i + p[i]); j++) g[i][0] = min(g[i][0], 1 - f[j]), g[i][1] = max(g[i][1], 1 - f[j]);
        f[i] = g[i][1];
        for (int j = i + 1; j < min(n, i + p[i]); j++)
            f[i] = max(f[i], h[0][p[i] - j + i][q[i] + q[j]] * g[j][0] + h[1][p[i] - j + i][q[i] + q[j]] * g[j][1] +
                                 (1 - h[0][p[i] - j + i][q[i] + q[j]] - h[1][p[i] - j + i][q[i] + q[j]]) * (1 - f[j]));
    }
    cout << setiosflags(ios::fixed) << setprecision(10) << f[0] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
