#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 300005

typedef pair<int, int> pii;

bool vis[maxn];
int dep[maxn], xx[maxn], yy[maxn], fa[maxn];

vector<vector<int>> graph, tree;
int to[maxn];

void dfs(int p) {
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i]) {
            tree[p].push_back(i);
            dep[i] = dep[p] + 1, fa[i] = p;
            dfs(i);
        }
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    graph.resize(n + 1), tree.resize(n + 1);
    for (int i = 1; i <= n; i++) vis[i] = false, to[i] = 0;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs(1);
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        xx[i] = x, yy[i] = y;
        if (to[x] == y) {
            to[x] = to[y] = 0;
            continue;
        }
        if (to[x]) tie(to[x], x) = make_tuple(0, to[x]);
        if (to[y]) tie(to[y], y) = make_tuple(0, to[y]);
        to[x] = y, to[y] = x;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (to[i]) cnt++;
    cnt /= 2;
    if (cnt == 0) {
        cout << "YES" << endl;
        for (int i = 1; i <= q; i++) {
            int x = xx[i], y = yy[i];
            static deque<int> d1, d2;
            d1.clear(), d2.clear();
            while (x != y) {
                if (dep[x] >= dep[y])
                    d1.push_back(x), x = fa[x];
                else
                    d2.push_front(y), y = fa[y];
            }
            cout << d1.size() + 1 + d2.size() << endl;
            for (auto i : d1) cout << i << ' ';
            cout << x;
            for (auto i : d2) cout << ' ' << i;
            cout << endl;
        }
    } else {
        cout << "NO" << endl
             << cnt << endl;
    }
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}