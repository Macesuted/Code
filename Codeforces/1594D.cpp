/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

vector<vector<int>> graph;

int cnt[3];
bool vis[maxn << 1];
int n, m;

void dfs(int p) {
    cnt[p <= n]++;
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i]) dfs(i);
    return;
}

void work(void) {
    cin >> n >> m;
    graph.clear();
    graph.resize(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) vis[i] = false;
    for (int i = 1; i <= m; i++) {
        int x, y;
        string c;
        cin >> x >> y >> c;
        if (c == "crewmate") {
            graph[x].push_back(y), graph[y].push_back(x);
            graph[x + n].push_back(y + n), graph[y + n].push_back(x + n);
        } else {
            graph[x].push_back(y + n), graph[y + n].push_back(x);
            graph[x + n].push_back(y), graph[y].push_back(x + n);
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        cnt[1] = cnt[0] = 0;
        dfs(i);
        if (vis[n + i]) {
            cout << -1 << endl;
            return;
        }
        answer += max(cnt[0], cnt[1]);
        dfs(n + i);
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}