/**
 * @file 102465H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        set<int> S;
        Node(void) { l = r = nullptr; }
    };

    Node *root;

    void insert(Node *&p, int l, int r, int px, int py) {
        if (!p) p = new Node();
        p->S.insert(py);
        if (l == r) return;
        int mid = (l + r) >> 1;
        return (px <= mid) ? insert(p->l, l, mid, px, py) : insert(p->r, mid + 1, r, px, py);
    }
    bool query(Node *&p, int l, int r, int px, int py) {
        if (!p) return true;
        if (r <= px) return p->S.upper_bound(py) == p->S.begin();
        int mid = (l + r) >> 1;
        if (px <= mid) return query(p->l, l, mid, px, py);
        return query(p->l, l, mid, px, py) && query(p->r, mid + 1, r, px, py);
    }

   public:
    SegmentTree(void) { root = nullptr; }
    void insert(int x, int y) { return insert(root, 0, 1e8, x, y); }
    bool query(int x, int y) { return query(root, 0, 1e8, x, y); }
} ST;

vector<pii> graph[maxn];
int dist[3][maxn];
bool vis[3][maxn];
priority_queue<pii, vector<pii>, greater<pii>> que;

void Dijkstra(int S) {
    que.emplace(dist[S][S] = 0, S);
    while (!que.empty()) {
        auto [dis, p] = que.top();
        que.pop();
        if (vis[S][p]) continue;
        vis[S][p] = true;
        for (auto [i, t] : graph[p])
            if (dist[S][i] > dis + t) que.emplace(dist[S][i] = dis + t, i);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0, x, y, t; i < m; i++) cin >> x >> y >> t, graph[x].emplace_back(y, t), graph[y].emplace_back(x, t);
    memset(dist, 0x3f, sizeof(dist)), Dijkstra(0), Dijkstra(1), Dijkstra(2);

    vector<tiii> cache;
    for (int i = 0; i < n; i++) cache.emplace_back(dist[0][i], dist[1][i], dist[2][i]);
    sort(cache.begin(), cache.end());

    int ans = 0;
    for (int i = 0, j; i < n; i = j + 1) {
        j = i;
        while (j + 1 < n && cache[i] == cache[j + 1]) j++;
        auto [x, y, z] = cache[i];
        if (!ST.query(y, z)) continue;
        ST.insert(y, z), ans += j - i + 1;
    }
    cout << ans << endl;

    return 0;
}