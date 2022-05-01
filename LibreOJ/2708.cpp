/**
 * @file 2708.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-23
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

#define maxn 3005
#define maxv 1000005

typedef pair<int, int> pii;

vector<vector<pii>> graph, ques;
int n, m, k, s;
long long dep[maxn];
int cnt1[maxv * 2], cnt2[maxv], dfni[maxn], dfno[maxn], nti[maxn];
bool ans[maxv];

int tim = 0;
void dfs1(int p) {
    nti[dfni[p] = ++tim] = p;
    for (auto i : graph[p]) dep[i.first] = dep[p] + i.second, dfs1(i.first);
    dfno[p] = tim;
    return;
}
void dfs2(int p) {
    for (int i = 0; i <= n; i++)
        if (dep[i] - dep[p] + s >= -maxv && dep[i] - dep[p] + s < maxv) cnt1[maxv + dep[i] - dep[p] + s]++;
    for (int i = dfni[p]; i <= dfno[p]; i++)
        if (dep[nti[i]] - dep[p] + s < maxv) cnt2[dep[nti[i]] - dep[p] + s]++;
    for (auto i : ques[p]) {
        if (i.first < -maxv || i.first >= maxv) continue;
        ans[i.second] = cnt1[maxv + i.first];
        for (int j = 1; j * j <= i.first && !ans[i.second]; j++) {
            if (i.first % j) continue;
            ans[i.second] = (cnt2[j] || cnt2[i.first / j]);
        }
    }
    for (auto i : graph[p]) dfs2(i.first);
    for (int i = 0; i <= n; i++)
        if (dep[i] - dep[p] + s >= -maxv && dep[i] - dep[p] + s < maxv) cnt1[maxv + dep[i] - dep[p] + s]--;
    for (int i = dfni[p]; i <= dfno[p]; i++)
        if (dep[nti[i]] - dep[p] + s < maxv) cnt2[dep[nti[i]] - dep[p] + s]--;
    return;
}

void solve(void) {
    n = read<int>(), m = read<int>(), k = read<int>(), s = read<int>() + 1;
    graph.resize(n + 1), ques.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int p = read<int>(), l = read<int>() + 1;
        graph[p].emplace_back(i, l);
    }
    dfs1(0);
    for (int i = 1; i <= m; i++) {
        int p = read<int>(), l = read<int>() + 1;
        if (k - l - dep[p] == 0)
            ans[i] = true;
        else
            ques[p].emplace_back(k - l - dep[p], i);
    }
    dfs2(0);
    for (int i = 1; i <= m; i++) putstr(ans[i] ? "YES" : "NO"), putch('\n');
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