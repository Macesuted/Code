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
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 100005

struct Edge {
    int from, to, dist;
    inline bool operator<(const Edge& oth) const { return this->dist > oth.dist; }
};

int c[maxn], fa[maxn << 1], v[maxn << 1], f[maxn << 1], siz[maxn << 1];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

vector<Edge> edges;
vector<vector<int>> tree;

void dfs(int p) {
    if (tree[p].empty()) return f[p] = 0x3f3f3f3f, siz[p] = c[p], void();
    int l = tree[p][0], r = tree[p][1];
    dfs(l), dfs(r), siz[p] = siz[l] + siz[r];
    f[p] = max(min({v[p] - siz[l], f[l], f[r] - siz[l]}), min({v[p] - siz[r], f[r], f[l] - siz[r]}));
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), dist = read<int>();
        edges.push_back({x, y, dist});
    }
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= 2 * n - 1; i++) fa[i] = i;
    int cnt = n;
    tree.resize(2 * n);
    for (auto i : edges) {
        if (getfa(i.from) == getfa(i.to)) continue;
        v[++cnt] = i.dist;
        tree[cnt].push_back(getfa(i.from)), tree[cnt].push_back(getfa(i.to));
        fa[getfa(i.from)] = fa[getfa(i.to)] = cnt;
    }
    int answer = 0;
    for (int i = 1; i <= cnt; i++)
        if (fa[i] == i) dfs(i), answer = f[i];
    cout << (answer > 0 ? answer : -1) << endl;
    return 0;
}