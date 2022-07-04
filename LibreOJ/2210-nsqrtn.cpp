/**
 * @file 2210-nsqrtn.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 256M
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
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
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxn 100005

int sg[maxn];
bool vis[30];

int F;

void solve(void) {
    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) ans ^= sg[read<int>()];
    write(int(ans != 0)), putch(' ');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    F = read<int>();
    for (int i = F; i < maxn; i++) {
        memset(vis, 0, sizeof(vis));
        for (int l = 2, r; l <= i; l = r + 1) {
            int p = i / l, c1 = i % l, c0 = l - c1, ans = 0;
            r = i / p;
            if (c0 & 1) ans ^= sg[p];
            if (c1 & 1) ans ^= sg[p + 1];
            vis[ans] = true;
            if (l < r) vis[ans ^ sg[p + (p & 1)]] = true;
        }
        sg[i] = 0;
        while (vis[sg[i]]) sg[i]++;
    }
    while (_--) solve();
    putch('\n');

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
