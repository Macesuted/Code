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

#define maxn 3005
#define maxlgn 14

bool b1;

vector<vector<int>> graph, tree;
vector<int> ring;
bool onRing[maxn], inStack[maxn];
int top[maxn];
int fa[maxn][maxlgn], dep[maxn];

bool b2;

stack<int> S;
bool findRing(int p, int pre = -1) {
    inStack[p] = true;
    S.push(p);
    for (auto i : graph[p]) {
        if (i == pre) continue;
        if (inStack[i]) {
            while (S.top() != i) ring.push_back(S.top()), onRing[S.top()] = true, S.pop();
            ring.push_back(i), onRing[i] = true;
            return true;
        }
        if (findRing(i, p)) return true;
    }
    S.pop();
    inStack[p] = false;
    return false;
}
void dfs1(int p, int _top, int pre = 0) {
    tree[top[p] = _top].push_back(p);
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p]) {
        if (i == pre || onRing[i]) continue;
        dfs1(i, _top, p);
    }
    return;
}
int LCA(int x, int y) {
    if (top[x] != top[y]) return 0;
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
inline int dist(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)] + 1; }

int main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(10);
    int n = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = read<int>() + 1, y = read<int>() + 1;
        graph[x].push_back(y), graph[y].push_back(x);
    }
    findRing(1);
    int m = ring.size();
    tree.resize(m);
    for (int i = 0; i < m; i++) dfs1(ring[i], i);
    double answer = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (top[i] == top[j])
                answer += 1.0 / dist(i, j);
            else {
                int x = top[i], y = top[j], dx = dep[i], dy = dep[j],
                    d1 = abs(x - y) - 1, d2 = m - d1 - 2;
                answer += 1.0 / (dx + d1 + dy) + 1.0 / (dx + d2 + dy) - 1.0 / (dx + d1 + d2 + dy);
            }
    cout << answer << endl;
    return 0;
}