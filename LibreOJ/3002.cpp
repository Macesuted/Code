/**
 * @file 3002.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-22
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

#define maxn 505

int f[maxn][maxn][2][2], C[maxn], A[maxn], V[maxn];

void qmax(int& a, int b) { return a = max(a, b), void(); }
bool same(int a, int b) { return C[a] == C[b] || A[a] == A[b]; }

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) C[i] = read<int>(), A[i] = read<int>(), V[i] = read<int>();
    C[n + 1] = A[n + 1] = 114514, C[n + 2] = A[n + 2] = 1919810;
    int ans = 0, minV = numeric_limits<int>::min();
    for (int a = 1; a <= n + 2; a++)
        for (int b = 1; b <= n + 2; b++)
            f[a][b][0][0] = f[a][b][0][1] = f[a][b][1][0] = f[a][b][1][1] = minV;
    f[1][2][1][0] = f[1][2][1][1] = 0;
    for (int c = 3; c <= n + 2; c++) {
        int tc = c & 1;
        for (int a = 1; a < c - 1; a++)
            for (int b = a + 1; b < c; b++) 
                if (f[a][b][tc][0] != minV || f[a][b][tc][1] != minV) {
                    int va = f[a][b][tc][0] + V[a], vc = f[a][b][tc][1] + V[c];
                    qmax(ans, va), qmax(ans, vc);
                    if (same(a, b)) qmax(f[b][c][!tc][0], va);
                    if (same(a, c + 1)) qmax(f[b][c][!tc][1], va);
                    if (same(c, a)) qmax(f[a][b][!tc][0], vc);
                    if (same(c, c + 1)) qmax(f[a][b][!tc][1], vc);
                    f[a][b][tc][0] = f[a][b][tc][1] = minV;
                }
    }
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
