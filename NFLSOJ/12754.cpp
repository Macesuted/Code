/**
 * @file dimoo.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-25
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

#define maxn 10000005

typedef pair<int, int> pii;

int a[maxn], b[maxn], c[maxn];
list<pii> li;

void solve(void) {
    int n = read<int>(), K_ = read<int>(), K = min(n, K_);
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += (a[i] = read<int>());
    for (int i = n; i > n - K; i--) {
        if (!a[i]) continue;
        int tim = n - i + 1;
        if (!li.empty() && li.back().second >= tim - 1)
            li.back().second += a[i];
        else
            li.emplace_back(tim, tim + a[i] - 1);
    }
    for (int i = 1; i <= n; i++) {
        while (!li.empty() && li.back().first + i - 1 > K) li.pop_back();
        if (!li.empty() && li.back().second + i - 1 >= K) b[i]++;
        while (!li.empty() && li.back().first + i > K) li.pop_back();
        if (!li.empty() && li.back().second + i > K) li.back().second = K - i;
        if (a[i]) {
            if (!li.empty() && li.front().first + i <= a[i] + 1)
                a[i] -= li.front().first + i - 1, li.front().first = 1 - i;
            else {
                int t = min(K, a[i]);
                li.emplace_front(1 - i, t - i), a[i] -= t;
            }
            while (a[i] && li.front().second + i < K) {
                auto p = ++li.begin();
                if (p != li.end() && p->first - li.front().second - 1 <= a[i])
                    a[i] -= p->first - li.front().second - 1, li.front().second = p->second, li.erase(p);
                else {
                    int t = min(a[i], K - li.front().second - i);
                    a[i] -= t, li.front().second += t;
                }
            }
            b[i] += a[i];
        }
    }
    if (sum < n && K_ > n) {
        int delt = K_ % n;
        for (int i = 1; i <= n; i++) c[i] = b[i];
        for (int i = 1; i <= delt; i++) b[i] = c[n + i - delt];
        for (int i = delt + 1; i <= n; i++) b[i] = c[i - delt];
    }
    unsigned long long M = 12345678901, f = 1, ans = 0;
    for (int i = 1; i <= n; i++) ans += (f *= M) * (unsigned long long)(b[i] + 1);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("dimoo.in", "r", stdin), freopen("dimoo.out", "w", stdout);
#endif
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