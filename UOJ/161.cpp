/**
 * @file 161.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-21
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

typedef tuple<int, int, int> tiii;

tiii a[maxn];
double f[maxn], g[maxn], ans[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) get<0>(a[i]) = read<int>(), get<2>(a[i]) = i;
    for (int i = 1; i <= n; i++) get<1>(a[i]) = get<0>(a[i]) - read<int>();
    sort(a + 1, a + n + 1,
         [](tiii a, tiii b) { return get<0>(a) != get<0>(b) ? get<0>(a) < get<0>(b) : get<1>(a) < get<1>(b); });
    for (int l = 1, r, minp = n + 1; l <= n; l = r + 1) {
        int p = lower_bound(a + 1, a + n + 1, tiii{get<1>(a[l]) + 1, 0, 0}) - a - 1;
        r = max(p, l);
        if (minp <= p)
            f[l] = 0;
        else if (p == r)
            f[l] = (l == 1 ? 0 : (r + g[l - 1]) / (l - 1));
        else
            f[l] = 1 + (p == 0 ? 0 : g[p] / p);
        if (f[l] == 0) minp = min(minp, l);
        for (int i = l; i <= r; i++) g[i] = g[i - 1] + (f[i] = f[l]);
    }
    for (int i = 1; i <= n; i++) ans[get<2>(a[i])] = f[i];
    cout << setiosflags(ios::fixed) << setprecision(5);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
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
