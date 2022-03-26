/**
 * @file 8252.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-26
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

vector<int> a[maxn];
int id[maxn], rec[maxn];
bool vis[maxn];

bool check(int x, int y) {
    bool p = false, q = false;
    for (auto i : a[x]) vis[i] = true;
    for (auto i : a[y]) (vis[i] ? p : q) = true;
    for (auto i : a[x]) vis[i] = false;
    return p && q;
}

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i].clear(), a[i].resize(read<int>());
        for (int j = 0; j < (int)a[i].size(); j++) a[i][j] = read<int>();
    }
    for (int i = 1; i <= n; i++) id[i] = i, rec[i] = 0;
    sort(id + 1, id + n + 1, [&](int x, int y) { return a[x].size() > a[y].size(); });
    for (int i = 1; i <= n; i++) {
        int w = 0;
        for (auto u : a[id[i]]) w = max(w, rec[u]);
        if (w && check(id[w], id[i])) return putstr("YES\n"), write(id[w]), putch(' '), write(id[i]), putch('\n');
        for (auto u : a[id[i]]) rec[u] = i;
    }
    return putstr("NO\n");
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
