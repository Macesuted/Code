/**
 * @file 7452.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define mod 1000000007
#define maxn 100005

typedef pair<int, int> pii;

int64_t C;

struct Value {
    int node, edge;
    bool operator<(const Value& o) const { return node * C + edge < o.node * C + o.edge; }
};

vector<vector<int>> graph;

Value f[maxn][2];
int val[maxn];
Value ans;

int read(void) {
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    int v = 0;
    while ('0' <= c && c <= '9') v = (v << 3) + (v << 1) + (c ^ 48), c = getchar();
    return v;
}

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void dfs1(int p, int pre = -1) {
    f[p][0].node = f[p][0].edge = f[p][1].node = f[p][1].edge = 0;
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p);
            Value x = f[i][0];
            x.edge++;
            if (f[p][0] < x)
                f[p][1] = f[p][0], f[p][0] = x;
            else if (f[p][1] < x)
                f[p][1] = x;
        }
    val[p] = graph[p].size() - 1, f[p][0].node += val[p], f[p][1].node += val[p];
    return;
}
void dfs2(int p, int pre = -1) {
    {
        Value x;
        x.node = f[p][0].node + f[p][1].node - int(graph[p].size() - 1);
        x.edge = f[p][0].edge + f[p][1].edge;
        if (ans < x) ans = x;
    }
    for (auto i : graph[p])
        if (i != pre) {
            Value b0 = f[i][0], b1 = f[i][1], v = f[p][0];
            if (f[p][0].edge == f[i][0].edge + 1 && f[p][0].node == f[i][0].node + val[p]) v = f[p][1];
            v.edge++, v.node += val[i];
            if (f[i][0] < v)
                f[i][1] = f[i][0], f[i][0] = v;
            else if (f[i][1] < v)
                f[i][1] = v;
            dfs2(i, p);
            f[i][0] = b0, f[i][1] = b1;
        }
    return;
}

void solve(void) {
    int n = read(), m = read();

    int64_t realC = (qpow(2, m) + mod - 1) % mod;
    C = 1;
    for (int i = 1; i <= min(m, 30); i++) C = min(C * 2, (int64_t)1e9);
    C--;

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) x = read(), y = read(), graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1);
    ans.edge = ans.node = 0;
    dfs2(1);

    cout << (ans.node * realC + ans.edge + 1) % mod << endl;
    return;
}

int main() {
    int _ = read();
    while (_--) solve();

    return 0;
}