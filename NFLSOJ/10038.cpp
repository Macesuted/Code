/**
 * @file 10038.cpp
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

#define maxn 200005

typedef pair<int, int> pii;

pii x[maxn];
vector<int> ansV, li;
long long ans = numeric_limits<long long>::max();

#define gen(i) abs(x[i].first - x[(i) + 1].first), (i)
void solve(int l, int r, int L, long long tot) {
    if (L > r - l - 1) return;
    tot += abs(x[l].first - x[r].first);
    static set<pii> use, unuse;
    use.clear(), unuse.clear();
    for (int i = l + 1; i < r - 1; i++) unuse.emplace(gen(i));
    long long nt = 0, pt = numeric_limits<int>::max();
    int pp = r;
    for (int i = 0; i < L && !unuse.empty(); i++)
        use.insert(*unuse.begin()), nt += 2 * unuse.begin()->first, unuse.erase(unuse.begin());
    pt = ((int)use.size() == L ? nt : numeric_limits<int>::max());
    for (int e = r - 1; e > l; e--) {
        nt += abs(x[e].first - x[e + 1].first);
        if (use.find({gen(e - 1)}) != use.end())
            nt -= 2 * abs(x[e - 1].first - x[e].first), use.erase({gen(e - 1)});
        else
            unuse.erase({gen(e - 1)});
        while ((int)use.size() + r - e > L) {
            if (use.empty()) break;
            unuse.insert(*use.rbegin()), nt -= 2 * use.rbegin()->first, use.erase(--use.end());
        }
        while ((int)use.size() + r - e < L) {
            if (unuse.empty()) break;
            use.insert(*unuse.begin()), nt += 2 * unuse.begin()->first, unuse.erase(unuse.begin());
        }
        if ((int)use.size() + r - e == L && pt > nt) pt = nt, pp = e;
    }
    L -= r - pp, tot += pt;
    use.clear(), unuse.clear();
    if (tot >= ans) return;
    static vector<bool> vis;
    vis.clear(), vis.resize(r + 1);
    for (int i = l + 1; i < pp - 1; i++) use.emplace(gen(i));
    for (int i = 0; i < L; i++) vis[use.begin()->second] = true, use.erase(use.begin());
    for (int i = pp; i < r; i++) vis[i] = true;
    for (int tl = l + 1, tr; tl <= r; tl = tr + 1) {
        tr = tl;
        while (vis[tr]) tr++;
        li.push_back(x[tr].second);
        for (int i = tr - 1; i >= tl; i--) li.push_back(x[i].second);
    }
    ans = tot, ansV = li;
    return;
}
#undef gen
void solve(int n, int L, int s) {
    if (s == n) return;
    li.clear();
    if (s == 1) return solve(1, n, L, 0);
    if (L == 0) return;
    long long tot = 2 * abs(x[1].first - x[s].first);
    int p = s;
    while (L > 1 && p > 1) li.push_back(x[--p].second), L--;
    if (p > 1) {
        for (int i = 1; i < p; i++) li.push_back(x[i].second);
        L--;
    }
    return solve(s, n, L, tot);
}
void solve(void) {
    int n = read<int>(), L = read<int>(), s = read<int>();
    for (int i = 1; i <= n; i++) x[i] = {read<int>(), i};
    solve(n, L, s), reverse(x + 1, x + n + 1), solve(n, n - L - 1, n - s + 1);
    if (ans == numeric_limits<long long>::max()) return putstr("-1\n");
    write(ans), putch('\n');
    for (auto i : ansV) write(i), putch(' ');
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("travel.in", "r", stdin), freopen("travel.out", "w", stdout);
#endif
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
