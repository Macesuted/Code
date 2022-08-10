/**
 * @file 2876.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxr 2005
#define maxn 200005
#define maxlgn 20

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int way[2][4] = {{0, 1, 0, -1}, {1, 0, -1, 0}};

string s[maxr];
int px[maxn], py[maxn], fa[maxn], f[maxn][maxlgn], g[maxn][maxlgn], dep[maxn], vis[maxn];
pii dist[maxr][maxr];
queue<pii> que;
vector<tiii> graph;
vector<pii> tree[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void dfs(int p, int id, int pre = 0) {
    vis[p] = id;
    for (int i = 1; i < maxlgn; i++) f[p][i] = f[f[p][i - 1]][i - 1], g[p][i] = max(g[p][i - 1], g[f[p][i - 1]][i - 1]);
    for (auto i : tree[p])
        if (i.first != pre) dep[i.first] = dep[p] + 1, f[i.first][0] = p, g[i.first][0] = i.second, dfs(i.first, id, p);
    return;
}
int getMaxEdge(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int d = 0;
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[f[x][i]] >= dep[y]) d = max(d, g[x][i]), x = f[x][i];
    if (x == y) return d;
    for (int i = maxlgn - 1; ~i; i--)
        if (f[x][i] != f[y][i]) d = max({d, g[x][i], g[y][i]}), x = f[x][i], y = f[y][i];
    return max({d, g[x][0], g[y][0]});
}

void solve(void) {
    int r, c, n, q;
    cin >> r >> c >> n >> q;
    for (int i = 1; i <= r; i++) cin >> s[i], s[i] = " " + s[i];
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= n; i++)
        cin >> px[i] >> py[i], dist[px[i]][py[i]] = {0, i}, que.emplace(px[i], py[i]), fa[i] = i;
    while (!que.empty()) {
        int px, py;
        tie(px, py) = que.front(), que.pop();
        for (int t = 0; t < 4; t++) {
            int wx = px + way[0][t], wy = py + way[1][t];
            if (1 <= wx && wx <= r && 1 <= wy && wy <= c && s[wx][wy] != '#' &&
                dist[wx][wy].first > dist[px][py].first + 1)
                dist[wx][wy] = {dist[px][py].first + 1, dist[px][py].second}, que.emplace(wx, wy);
        }
    }
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) {
            if (i != r && dist[i][j].first != 0x3f3f3f3f && dist[i + 1][j].first != 0x3f3f3f3f &&
                dist[i][j].second != dist[i + 1][j].second)
                graph.emplace_back(dist[i][j].first + dist[i + 1][j].first, dist[i][j].second, dist[i + 1][j].second);
            if (j != c && dist[i][j].first != 0x3f3f3f3f && dist[i][j + 1].first != 0x3f3f3f3f &&
                dist[i][j].second != dist[i][j + 1].second)
                graph.emplace_back(dist[i][j].first + dist[i][j + 1].first, dist[i][j].second, dist[i][j + 1].second);
        }
    sort(graph.begin(), graph.end());
    for (auto i : graph) {
        int w, x, y;
        tie(w, x, y) = i;
        if (getfa(x) == getfa(y)) continue;
        fa[getfa(x)] = getfa(y);
        tree[x].emplace_back(y, w), tree[y].emplace_back(x, w);
    }
    for (int i = 1, j = 0; i <= n; i++)
        if (!vis[i]) dfs(i, ++j);
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (vis[x] != vis[y])
            cout << -1 << endl;
        else
            cout << getMaxEdge(x, y) << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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