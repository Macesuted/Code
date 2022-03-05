/**
 * @file minion.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-05
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 3S  Memory Limit: 256M
 *
 */

#include <bits/stdc++.h>

namespace io {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
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
std::string getstr(const std::string& suf = "") {
    std::string s = suf;
    char c = getch();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r') c = getch();
    Il--;
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && *Il != ' ' && *Il != '\t' && *Il != '\n' && *Il != '\v' && *Il != '\f' && *Il != '\r' && *Il != EOF)
            Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(std::string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::buftop;
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::tie;

bool mem1;

#define maxn 1000005

typedef std::pair<long long, long long> pll;

pll a[maxn], f[maxn], g[maxn];
int n;

pll solve(long long lim) {
    f[0] = g[0] = {0, 0};
    for (int i = 1, p = 0; i <= n; i++) {
        while (p < i && a[p].second < a[i].first) p++;
        f[i] = {0, 0};
        if (p < i) f[i] = max(f[i], pll{f[p].first + a[i].second - a[p].second - lim, f[p].second + 1});
        f[i] = max(f[i], pll{g[p - 1].first + a[i].second - a[i].first + 1 - lim, g[p - 1].second + 1});
        g[i] = max(f[i], g[i - 1]);
    }
    return {g[n].first, g[n].second};
}

void solve(void) {
    n = read<int>();
    int m = read<int>();
    for (int i = 1; i <= n; i++) a[i].first = read<long long>(), a[i].second = read<long long>() - 1;
    sort(a + 1, a + n + 1, [](pll x, pll y) { return x.first < y.first || (x.first == y.first && x.first > y.first); });
    int tn = n;
    n = 1;
    for (int i = 2; i <= tn; i++)
        if (a[i].second > a[n].second) a[++n] = a[i];
    long long l = 0, r = 1e18, ans, cnt;
    tie(ans, cnt) = solve(0);
    if (cnt <= m) return write(ans), putch('\n');
    while (l + 1 < r) {
        long long mid = (l + r) >> 1;
        tie(ans, cnt) = solve(mid);
        cnt > m ? l = mid : r = mid;
    }
    tie(ans, cnt) = solve(r);
    assert(cnt <= m);
    write(ans + cnt * r), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("minion.in", "r", stdin), freopen("minion.out", "w", stdout);
#endif
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
