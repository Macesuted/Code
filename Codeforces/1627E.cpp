/**
 * @file 1627E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define int long long

#define maxn 1000005

typedef pair<int, int> pii;
typedef pair<int, long long> pil;
typedef pair<long long, int> pli;
typedef tuple<int, long long, int> tili;
typedef tuple<int, int, int> tiii;

map<pii, int> pti;
pii itp[maxn * 2];

int x[maxn];
long long dist[maxn * 2];
bool vis[maxn * 2];
int cnt;

int getId(int x, int y) {
    if (pti.find({x, y}) == pti.end()) itp[pti[{x, y}] = ++cnt] = {x, y};
    return pti[{x, y}];
}

vector<set<pii>> line;
vector<tiii> edges;
vector<vector<pil>> graph;

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    pti.clear();
    line.clear(), line.resize(n + 1);
    edges.clear();
    cnt = 0;
    for (int i = 1; i <= n; i++) cin >> x[i];
    line[1].emplace(1, getId(1, 1)), line[n].emplace(m, getId(n, m));
    for (int i = 1; i <= k; i++) {
        int r1, c1, r2, c2, h;
        cin >> r1 >> c1 >> r2 >> c2 >> h;
        int p1 = getId(r1, c1), p2 = getId(r2, c2);
        line[r1].emplace(c1, p1), line[r2].emplace(c2, p2);
        edges.emplace_back(p1, p2, -h);
    }
    graph.clear(), graph.resize(cnt + 1);
    for (auto i : edges) graph[get<0>(i)].emplace_back(get<1>(i), get<2>(i));
    for (int i = 1; i <= n; i++)
        if (!line[i].empty()) {
            auto j = line[i].begin();
            int last = j->second, lastp = j->first;
            while (++j != line[i].end())
                graph[j->second].emplace_back(last, 1LL * abs(j->first - lastp) * x[i]),
                    graph[last].emplace_back(j->second, 1LL * abs(j->first - lastp) * x[i]), last = j->second, lastp = j->first;
        }
    static priority_queue<tili, vector<tili>, greater<tili>> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= cnt; i++) dist[i] = 0x3f3f3f3f3f3f3f3f, vis[i] = false;
    que.emplace(1, dist[1] = 0, 1);
    while (!que.empty()) {
        int p = get<2>(que.top());
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second)
                que.emplace(itp[i.first].first, dist[i.first] = dist[p] + i.second, i.first);
    }
    if (dist[2] == 0x3f3f3f3f3f3f3f3f)
        cout << "NO ESCAPE" << endl;
    else
        cout << dist[2] << endl;
    return;
}

bool mem2;

signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
