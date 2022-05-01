/**
 * @file 2707.cpp
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

#define maxn 60005

typedef pair<int, int> pii;

vector<vector<pii>> graph;
bool vis[maxn], inr[maxn];
vector<pii> S, ring;
map<int, int> a;
bitset<1200005> F;

int ecnt, vcnt;
void dfs(int p, int pre = -1) {
    if (vis[p]) {
        bool check = false;
        for (auto i = S.rbegin(); i != S.rend(); i++) check |= (i->first == p);
        if (!check) return;
        for (auto i = S.rbegin(); (i - 1)->first != p; i++) ring.push_back(*i);
        return;
    }
    vis[p] = true;
    vcnt++, ecnt += graph[p].size();
    for (auto i : graph[p])
        if (i.first != pre)
            S.emplace_back(p, i.second), dfs(i.first, p), S.pop_back();
        else
            pre = -1;
    return;
}
int tn, base = 0;
void dfs2(int p, int pre) {
    for (auto i : graph[p])
        if (i.first != pre) base += (i.first > tn ? -1 : +1) * i.second, dfs2(i.first, p);
    return;
}

void solve(void) {
    int n = read<int>() * 2, k = read<int>();
    tn = n / 2;
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>() + tn, s = read<int>();
        graph[x].emplace_back(y, s), graph[y].emplace_back(x, s);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        ecnt = vcnt = 0, ring.clear(), dfs(i);
        if (vcnt * 2 != ecnt) return putstr("NO\n");
        int sum[2] = {0, 0};
        for (int i = 0; i < (int)ring.size(); i++) sum[i & 1] += ring[i].second, inr[ring[i].first] = true;
        for (auto i : ring)
            for (auto j : graph[i.first])
                if (!inr[j.first]) base += (j.first > tn ? -1 : +1) * j.second, dfs2(j.first, i.first);
        tie(sum[0], sum[1]) = make_pair(sum[0] - sum[1], sum[1] - sum[0]);
        base += min(sum[0], sum[1]), a[max(sum[0], sum[1]) - min(sum[0], sum[1])]++;
    }
    F[0] = true;
    for (auto i : a)
        for (int j = 1; i.second; i.second -= j, j = min(j + j, i.second)) F |= F << (i.first * j);
    for (int i = max(0, -k - base); i <= +k - base; i++)
        if (F[i]) return putstr("YES\n");
    return putstr("NO\n");
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
