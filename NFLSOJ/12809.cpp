/**
 * @file twilight.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-24
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

#define maxn 1005

vector<vector<int>> graph;
int ori[maxn][maxn], c[maxn], f[maxn];
vector<int> a;
bool vis[maxn];

int cnt[2];
void dfs(int p, int col = 1) {
    vis[p] = true, cnt[(c[p] = col) - 1]++;
    for (auto i : graph[p])
        if (!vis[i])
            dfs(i, 3 - col);
        else if (c[i] == col)
            putstr("-1\n"), exit(0);
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        ori[x][y] = ori[y][x] = true;
    }
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!ori[i][j] && i != j) graph[i].push_back(j);
    int base = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            cnt[0] = cnt[1] = 0;
            dfs(i);
            base += min(cnt[0], cnt[1]), a.push_back(max(cnt[0], cnt[1]) - min(cnt[0], cnt[1]));
        }
    f[base] = true;
    for (auto i : a)
        for (int j = n; j >= i; j--) f[j] |= f[j - i];
    for (int i = n / 2; i; i--)
        if (f[i]) return write(i), putch('\n');
    return putstr("-1\n");
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("twilight.in", "r", stdin), freopen("twilight.out", "w", stdout);
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
