/**
 * @file 1625E2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
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

#define maxn 300005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    vector<long long> tree;

   public:
    void resize(int n) { return tree.resize(n + 1); }
    void add(int p, long long val) {
        for (int i = p; i < (int)tree.size(); i += i & -i) tree[i] += val;
        return;
    }
    long long sum(int p) {
        long long sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT, sons[maxn];

bool a[maxn];
pii b[maxn];
int bel[maxn], cnt = 0;
int dfni[maxn], dfno[maxn], fa[maxn], son[maxn], dfnCnt = 0;

vector<set<int>> graph;

void dfs(int p, int pre = -1, int sonId = 0) {
    fa[p] = pre, son[p] = sonId;
    dfni[p] = ++dfnCnt;
    FT.add(dfni[p], (long long)graph[p].size() * ((long long)graph[p].size() + 1) / 2);
    sons[p].resize(graph[p].size());
    int cnt = 0;
    for (auto i : graph[p]) dfs(i, p, ++cnt), sons[p].add(cnt, 1);
    dfno[p] = dfnCnt;
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        char c = getch();
        while (c != '(' && c != ')') c = getch();
        a[i] = (c == '(');
    }
    stack<int> S;
    for (int i = 1; i <= n; i++)
        if (a[i])
            S.push(i);
        else if (!S.empty())
            bel[S.top()] = bel[i] = ++cnt, b[cnt] = {S.top(), i}, S.pop();
    while (!S.empty()) S.pop();
    for (int i = n; i; i--)
        if (a[i] && bel[i]) {
            while (!S.empty() && b[S.top()].second < b[bel[i]].second) graph[bel[i]].insert(S.top()), S.pop();
            S.push(bel[i]);
        }
    while (!S.empty()) graph[0].insert(S.top()), S.pop();
    FT.resize(cnt + 1);
    dfs(0);
    while (m--) {
        int t = read<int>(), l = read<int>(), r = read<int>(), f = fa[bel[l]];
        if (t == 1) {
            FT.add(dfni[f], -(long long)graph[f].size() * ((long long)graph[f].size() + 1) / 2);
            graph[f].erase(bel[l]);
            FT.add(dfni[f], +(long long)graph[f].size() * ((long long)graph[f].size() + 1) / 2);
            sons[f].add(son[bel[l]], -1);
        } else {
            long long cnt = sons[f].sum(son[bel[r]]) - sons[f].sum(son[bel[l]] - 1);
            write(FT.sum(dfno[bel[r]]) - FT.sum(dfni[bel[l]] - 1) + cnt * (cnt + 1) / 2), putch('\n');
        }
    }
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
