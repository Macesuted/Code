/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar())
        x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 100005
#define maxc 1000005
#define maxlgn 20

struct Edge {
    int from, to, dist;
    inline bool operator<(const Edge& oth) const { return this->dist < oth.dist; }
};

int c[maxn], fa[maxn << 1], v[maxn << 1], siz[maxn << 1], son[maxn << 1], f[maxn << 1][maxlgn];
int cnt[maxn], high = 0;
int answer[maxn << 1];

vector<Edge> edges;
vector<vector<int>> graph;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void dfs1(int p, int pre = 0) {
    f[p][0] = pre;
    for (int i = 1; i < maxlgn; i++) f[p][i] = f[f[p][i - 1]][i - 1];
    siz[p] = 1, son[p] = 0;
    for (auto i : graph[p]) {
        dfs1(i, p);
        siz[p] += siz[i];
        if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
    }
    return;
}
void clear(int p) {
    if (graph[p].empty()) cnt[c[p]]--;
    for (auto i : graph[p]) clear(i);
    return;
}
void dfs2(int p, bool getAns = true) {
    if (graph[p].empty()) {
        cnt[c[p]]++;
        if (cnt[c[p]] > cnt[high] || (cnt[c[p]] == cnt[high] && c[p] < high)) high = c[p];
        if (getAns) answer[p] = high;
        return;
    }
    if (getAns) {
        for (auto i : graph[p])
            if (i != son[p]) dfs2(i, true), clear(i);
    }
    dfs2(son[p], getAns);
    for (auto i : graph[p])
        if (i != son[p]) dfs2(i, false);
    if (getAns) answer[p] = high;
    return;
}

struct constructure {
    constructure(int n) {
        graph.resize(n << 1);
    }
    ~constructure() {
        edges.clear();
        graph.clear();
    }
};

void solve(void) {
    int n = read<int>(), m = read<int>();
    constructure __constructure(n);
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        edges.push_back({x, y, z});
    }
    sort(edges.begin(), edges.end());
    v[0] = 0x3f3f3f3f;
    for (int i = 1; i <= n * 2; i++) fa[i] = i, v[i] = -0x3f3f3f3f;
    int cnt = n;
    for (auto i : edges) {
        if (getfa(i.from) == getfa(i.to)) continue;
        v[++cnt] = i.dist;
        graph[cnt].push_back(getfa(i.from)), graph[cnt].push_back(getfa(i.to));
        fa[getfa(i.from)] = fa[getfa(i.to)] = cnt;
    }
    for (int i = 1; i <= cnt; i++)
        if (fa[i] == i) graph[0].push_back(i);
    dfs1(0), dfs2(0), clear(0);
    int q = read<int>(), lastans = 0;
    while (q--) {
        int x = read<int>() ^ lastans, w = read<int>() ^ lastans;
        for (int i = maxlgn - 1; ~i; i--)
            if (v[f[x][i]] <= w) x = f[x][i];
        cout << (lastans = answer[x]) << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = read<int>();
    for (int __ = 1; __ <= _; __++) {
        cout << "Case #" << __ << ":" << endl;
        solve();
    }
    return 0;
}