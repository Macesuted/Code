/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

struct edge {
    int v, w, next;
} e[maxn * 4];
int head[maxn], tot[maxn], dis[maxn], vis[maxn], cnt = 0;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
bool spfa(int s) {
    queue<int> q;
    memset(dis, 63, sizeof(dis));
    dis[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) {
                    vis[v] = 1, tot[v]++;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        addedge(n + 1, i, 0);
    for (int i = 1; i <= n; i++) addedge(i - 1, i, 1), addedge(i, i - 1, 0);
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        addedge(r, l - 1, -x);
    }
    spfa(n + 1);
    for (int i = 1; i <= n; i++) cout << dis[i] - dis[i - 1] << ' ';
    return 0;
}