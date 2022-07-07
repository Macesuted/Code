/**
 * @file 2138.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Solution: https://macesuted.moe/article/loj2138
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 105
#define eps 1e-9
#define feps 1e-11

bool con[maxn][maxn];
int n, m, a[maxn], b[maxn], c[maxn], d[maxn];

class Frac {
   private:
    int64_t x, y;

    int64_t gcd(int64_t a, int64_t b) { return b ? gcd(b, a % b) : a; }

   public:
    Frac(int64_t x_ = 0, int64_t y_ = 1) {
        int64_t g = gcd(x_, y_);
        x = x_ / g, y = y_ / g;
    }
    operator double() { return (double)x / y; }
    operator int64_t() { return x / y; }
    Frac operator+(const Frac& o) const { return Frac(x * o.y + y * o.x, y * o.y); }
    Frac operator-(const Frac& o) const { return Frac(x * o.y - y * o.x, y * o.y); }
    Frac operator*(const Frac& o) const { return Frac(x * o.x, y * o.y); }
    Frac operator/(const Frac& o) const { return Frac(x * o.y, y * o.x); }
    bool operator==(const Frac& o) const { return x == o.x && y == o.y; }
    Frac& operator+=(const Frac& o) { return *this = *this + o; }
    Frac& operator-=(const Frac& o) { return *this = *this - o; }
    Frac& operator*=(const Frac& o) { return *this = *this * o; }
    Frac& operator/=(const Frac& o) { return *this = *this / o; }
    void print(void) {
        if (y < 0) x = -x, y = -x;
        return cout << x << '/' << y, void();
    }
};

typedef pair<Frac, Frac> pff;

class Dinic {
   private:
    struct Edge {
        int to, rev;
        double cap;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;

    bool bfs(void) {
        for (int i = 1; i <= n + m + 2; i++) dist[i] = -1, cur[i] = graph[i].begin();
        que.push(n + m + 1), dist[n + m + 1] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap > feps && !~dist[i.to]) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return ~dist[n + m + 2];
    }
    double dfs(int p, double rest) {
        if (rest < feps || p == n + m + 2) return rest;
        double use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest > feps; i++) {
            cur[p] = i;
            if (dist[p] + 1 != dist[i->to] || i->cap < feps) continue;
            if ((c = dfs(i->to, min(rest, i->cap))) < feps) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, use += c, rest -= c;
        }
        return use;
    }

   public:
    void addEdge(int from, int to, double cap) {
        return graph[from].push_back(Edge{to, (int)graph[to].size(), cap}),
               graph[to].push_back(Edge{from, (int)graph[from].size() - 1, 0});
    }
    pff dinic(double lim) {
        graph.clear(), graph.resize(n + m + 3), cur.resize(n + m + 3), dist.resize(n + m + 3);
        for (int i = 1; i <= n; i++)
            if (a[i] == 0) {
                if (b[i] < lim) addEdge(n + m + 1, i, c[i]);
            } else
                addEdge(n + m + 1, i, min((lim - b[i]) / 2. / a[i], (double)c[i]));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (con[i][j]) addEdge(i, n + j, 1e18);
        for (int i = 1; i <= m; i++) addEdge(n + i, n + m + 2, d[i]);
        while (bfs()) dfs(n + m + 1, 1e18);
        Frac K, B;
        for (int i = 1; i <= n; i++)
            if (dist[i] == -1) {
                if (a[i] == 0) {
                    if (b[i] < lim) B += Frac(c[i]);
                } else if (lim > 2 * a[i] * c[i] + b[i])
                    B += Frac(c[i]);
                else if (lim > b[i])
                    K += Frac(1, 2 * a[i]), B -= Frac(b[i], a[i] * 2);
            }
        for (int i = 1; i <= m; i++)
            if (~dist[n + i]) B += Frac(d[i]);
        return {K, B};
    }
} net;

vector<pff> nodes;

void solve(pff l, pff r) {
    if (l == r) return;
    Frac mid = (l.second - r.second) / (r.first - l.first);
    pff fml = net.dinic((double)mid - eps), fmr = net.dinic((double)mid + eps);
    if (l == fml) return nodes.emplace_back(mid, fml.first * mid + fml.second), void();
    return solve(l, fml), solve(fmr, r);
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= m; i++) cin >> d[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> con[i][j];
    cout << int64_t(net.dinic(1e18).second) << endl;
    nodes.emplace_back(Frac(), Frac());
    for (int i = 1; i <= 3; i++) {
        auto l = net.dinic(i - 1 + eps), r = net.dinic(i - eps);
        solve(l, r);
        nodes.emplace_back(Frac(i), Frac(i) * r.first + r.second);
    }
    solve(net.dinic(3 + eps), net.dinic(1e18));
    Frac ans;
    for (int i = 1; i < (int)nodes.size(); i++) {
        pff f1 = net.dinic((double)nodes[i - 1].first + eps), f2 = net.dinic((double)nodes[i].first - eps),
            f3 = net.dinic((double)nodes[i].first + eps);
        ans += Frac(1, 2) * (nodes[i].second - f1.first * nodes[i - 1].first - f1.second) *
                   (nodes[i - 1].first + nodes[i].first) +
               nodes[i].first * (f3.first * nodes[i].first + f3.second - f2.first * nodes[i].first - f2.second);
    }
    ans.print(), cout << endl;
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