/**
 * @file 2790.cpp
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

void solve(void) {
    int W = read<int>(), H = read<int>();
    vector<vector<long long>> A(W + 3, vector<long long>(H + 3)), ar, ac, ax, ay;
    ar = ac = ax = ay = A;
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>(), a = read<int>(), b = read<int>(), d = (a - 1) / b + 1;
        A[max(1, x - d + 1)][max(1, y - d + 1)] += a - (d - 1) * b,
            A[min(W + 1, x + d)][min(H + 1, y + d)] += a - (d - 1) * b;
        A[max(1, x - d + 1)][min(H + 1, y + d)] -= a - (d - 1) * b,
            A[min(W + 1, x + d)][max(1, y - d + 1)] -= a - (d - 1) * b;
        d--;
        {
            int dx = x - d, dy = y - d, xl = max(0, 1 - dx - 1), yl = max(0, 1 - dy - 1);
            A[1][1] += 1LL * min(xl, yl) * b;
            if (xl > yl) ac[1][dy + yl + 1] += b, ac[1][dy + xl + 1] -= b;
            if (yl > xl) ar[dx + xl + 1][1] += b, ar[dx + yl + 1][1] -= b;
            ax[dx + max(xl, yl) + 1][dy + max(xl, yl) + 1] += b;
        }
        {
            int dx = x - d, dy = y + d + 1, xl = max(0, 1 - dx - 1), yl = max(0, dy - (H + 1) - 1);
            A[1][H + 1] -= 1LL * min(xl, yl) * b;
            if (xl > yl) ac[1][dy - xl] -= b, ac[1][dy - yl] += b;
            if (yl > xl) ar[dx + xl + 1][H + 1] -= b, ar[dx + yl + 1][H + 1] += b;
            ay[dx + max(xl, yl) + 1][dy - max(xl, yl) - 1] -= b;
        }
        {
            int dx = x + d + 1, dy = y - d, xl = max(0, dx - (W + 1) - 1), yl = max(0, 1 - dy - 1);
            A[W + 1][1] -= 1LL * min(xl, yl) * b;
            if (xl > yl) ac[W + 1][dy + yl + 1] -= b, ac[W + 1][dy + xl + 1] += b;
            if (yl > xl) ar[dx - yl][1] -= b, ar[dx - xl][1] += b;
            ay[dx - max(xl, yl)][dy + max(xl, yl)] += b;
        }
        {
            int dx = x + d + 1, dy = y + d + 1, xl = max(0, dx - (W + 1) - 1), yl = max(0, dy - (H + 1) - 1);
            A[W + 1][H + 1] += 1LL * min(xl, yl) * b;
            if (xl > yl) ac[W + 1][dy - xl] += b, ac[W + 1][dy - yl] -= b;
            if (yl > xl) ar[dx - yl][H + 1] += b, ar[dx - xl][H + 1] -= b;
            ax[dx - max(xl, yl)][dy - max(xl, yl)] -= b;
        }
    }
    for (int i = 1; i <= W + 2; i++)
        for (int j = 0; j <= H + 2; j++) ar[i][j] += ar[i - 1][j];
    for (int i = 0; i <= W + 2; i++)
        for (int j = 1; j <= H + 2; j++) ac[i][j] += ac[i][j - 1];
    for (int i = 1; i <= W + 2; i++)
        for (int j = 1; j <= H + 2; j++) ax[i][j] += ax[i - 1][j - 1];
    for (int i = 1; i <= W + 2; i++)
        for (int j = H + 1; ~j; j--) ay[i][j] += ay[i - 1][j + 1];
    for (int i = 1; i <= W + 1; i++)
        for (int j = 1; j <= H + 1; j++) A[i][j] += ar[i][j] + ac[i][j] + ax[i][j] + ay[i][j];
    for (int i = 1; i <= W; i++)
        for (int j = 1; j <= H; j++) A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    for (int i = 1; i <= W; i++)
        for (int j = 1; j <= H; j++) A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    int q = read<int>();
    while (q--) {
        int l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>();
        long long t = A[l2][r2] - A[l1 - 1][r2] - A[l2][r1 - 1] + A[l1 - 1][r1 - 1], s = (r2 - r1 + 1) * (l2 - l1 + 1);
        long long ans = t / s;
        if (t % s * 2 >= s) ans++;
        write(ans), putch('\n');
    }
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
