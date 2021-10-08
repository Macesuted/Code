/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/lg4899
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

#define maxn 200005
#define maxlgn 20

typedef pair<int, int> pii;

class KruscalTree {
   private:
    int f[maxn];
    bool vis[maxn];

    int getfa(int p) { return f[p] == p ? p : f[p] = getfa(f[p]); }

   public:
    vector<vector<int>> tree;
    int fa[maxn][maxlgn], dfni[maxn], dfno[maxn], tim = 0;
    void dfs(int p, int pre) {
        dfni[p] = ++tim;
        fa[p][0] = pre;
        for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
        for (auto i : tree[p]) dfs(i, p);
        dfno[p] = tim;
        return;
    }
    void build(int n, const vector<vector<int>>& graph, int p[]) {
        for (int i = 1; i <= n; i++) vis[i] = false, f[i] = i;
        tree.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            vis[p[i]] = true;
            for (auto j : graph[p[i]])
                if (vis[j] && getfa(p[i]) != getfa(j))
                    tree[p[i]].push_back(getfa(j)), f[getfa(j)] = p[i];
        }
        return dfs(p[n], p[n]);
    }
} T[2];
class BIT {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} bit;

struct Ask {
    int l, r, id, op;
};

int p[maxn];

vector<vector<int>> graph;
vector<Ask> asks[maxn];
int points[maxn];
int answer[maxn];

int main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int n = read<int>(), m = read<int>(), q = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>() + 1, y = read<int>() + 1;
        graph[x].push_back(y), graph[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) p[i] = n - i + 1;
    T[0].build(n, graph, p), reverse(p + 1, p + n + 1), T[1].build(n, graph, p);
    for (int i = 1; i <= n; i++) points[T[0].dfni[i]] = T[1].dfni[i];
    for (int i = 1; i <= q; i++) {
        int S = read<int>() + 1, E = read<int>() + 1, l = read<int>() + 1, r = read<int>() + 1;
        for (int i = maxlgn - 1; ~i; i--)
            if (T[0].fa[S][i] >= l) S = T[0].fa[S][i];
        for (int i = maxlgn - 1; ~i; i--)
            if (T[1].fa[E][i] <= r) E = T[1].fa[E][i];
        if (T[0].dfni[S] - 1) asks[T[0].dfni[S] - 1].push_back({T[1].dfni[E], T[1].dfno[E], i, -1});
        asks[T[0].dfno[S]].push_back({T[1].dfni[E], T[1].dfno[E], i, +1});
    }
    for (int i = 1; i <= n; i++) {
        bit.add(points[i], +1);
        for (auto j : asks[i]) answer[j.id] += j.op * (bit.sum(j.r) - bit.sum(j.l - 1));
    }
    for (int i = 1; i <= q; i++) cout << (answer[i] >= 1) << endl;
    return 0;
}