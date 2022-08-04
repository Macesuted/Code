/**
 * @file 704E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-20
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf704e
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

#define maxn 100005
#define eps 1e-10

typedef pair<int, int> pii;
typedef tuple<int, long double, int, long double> tidid;

long double TIM, ans = numeric_limits<long double>::max();

struct comp {
    long double getPos(const tidid& a) const {
        return get<1>(a) == get<3>(a)
                   ? get<0>(a)
                   : get<0>(a) + (TIM - get<1>(a)) * (get<2>(a) - get<0>(a)) / (get<3>(a) - get<1>(a));
    }
    bool operator()(const tidid& a, const tidid& b) const { return getPos(a) < getPos(b); }
};

vector<vector<int>> graph;
int fa[maxn], siz[maxn], son[maxn], top[maxn], dep[maxn];
vector<tidid> heav[maxn], ligh[maxn];

void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != fa[p]) {
            fa[i] = p, dep[i] = dep[p] + 1, dfs1(i), siz[p] += siz[i];
            if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
void dfs2(int p, int top_) {
    top[p] = top_;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i != fa[p] && i != son[p]) dfs2(i, i);
    return;
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
void calcCross(tidid a, tidid b) {
    long double ak = (get<2>(a) - get<0>(a)) / (get<3>(a) - get<1>(a)),
                bk = (get<2>(b) - get<0>(b)) / (get<3>(b) - get<1>(b)), ad = get<0>(a) - get<1>(a) * ak,
                bd = get<0>(b) - get<1>(b) * bk;
    if ((ad < bd) != (ad + ak * TIM < bd + bk * TIM)) return;
    long double ret = (ad - bd) / (bk - ak);
    if (ret < max(get<1>(a), get<1>(b)) - eps || ret > min(get<3>(a), get<3>(b)) + eps) return;
    return ans = min(ans, ret), void();
}
void calc(vector<tidid>& a) {
    static vector<long double> pos;
    static vector<vector<tidid>> in, out;
    pos.clear(), pos.reserve(2 * a.size()), in.clear(), out.clear();
    for (auto i : a) pos.push_back(get<1>(i)), pos.push_back(get<3>(i));
    sort(pos.begin(), pos.end()), pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
    in.resize(pos.size()), out.resize(pos.size());
    for (auto i : a)
        in[lower_bound(pos.begin(), pos.end(), get<1>(i)) - pos.begin()].push_back(i),
            out[lower_bound(pos.begin(), pos.end(), get<3>(i)) - pos.begin()].push_back(i);
    static set<tidid, comp> S1;
    S1.clear();
    for (int i = 0; i < (int)pos.size(); i++) {
        TIM = pos[i];
        if (TIM > ans) return;
        for (auto j : in[i]) {
            auto ret = S1.emplace(j);
            if (!ret.second) return ans = min(ans, pos[i]), void();
            auto pl = ret.first, pr = pl;
            if (pl != S1.begin()) calcCross(*--pl, j);
            if (++pr != S1.end()) calcCross(j, *pr);
        }
        for (auto j : out[i]) {
            auto p2 = S1.erase(S1.find(j)), p1 = p2;
            if (p1 != S1.begin() && p2 != S1.end()) calcCross(*--p1, *p2);
        }
    }
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        long double tim = read<int>(), c = read<int>();
        int x = read<int>(), y = read<int>(), t = LCA(x, y);
        while (top[x] != top[t]) {
            heav[top[x]].emplace_back(x, tim, top[x], tim + (dep[x] - dep[top[x]]) / c),
                tim += (dep[x] - dep[top[x]]) / c, x = top[x];
            ligh[x].emplace_back(x, tim, fa[x], tim + 1 / c), tim += 1 / c, x = fa[x];
        }
        static stack<pii> cache;
        while (!cache.empty()) cache.pop();
        while (top[y] != top[t]) cache.emplace(y, top[y]), y = fa[top[y]];
        heav[top[y]].emplace_back(x, tim, y, tim + abs(dep[x] - dep[y]) / c), tim += abs(dep[x] - dep[y]) / c;
        while (!cache.empty()) {
            pii p = cache.top();
            cache.pop();
            ligh[p.second].emplace_back(fa[p.second], tim, p.second, tim + 1 / c), tim += 1 / c;
            heav[p.second].emplace_back(p.second, tim, p.first, tim + (dep[p.first] - dep[p.second]) / c),
                tim += (dep[p.first] - dep[p.second]) / c;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (auto& j : heav[i]) get<0>(j) = dep[get<0>(j)] - dep[i] + 1, get<2>(j) = dep[get<2>(j)] - dep[i] + 1;
        for (auto& j : ligh[i]) get<0>(j) = dep[get<0>(j)] - dep[i] + 2, get<2>(j) = dep[get<2>(j)] - dep[i] + 2;
        calc(heav[i]), calc(ligh[i]);
    }
    if (ans == numeric_limits<long double>::max()) return putstr("-1\n");
    cout << setiosflags(ios::fixed) << setprecision(30) << ans << endl;
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
