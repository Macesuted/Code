/**
 * @file 2117.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 105
#define mod 1000000007

typedef pair<int, int> pii;

class UnionSet {
   private:
    int fa[maxn];

   public:
    void init(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
        return;
    }
    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    bool merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return false;
        return fa[fx] = fy, true;
    }
} US;

vector<pii> edges;
vector<int> graph[maxn];
int siz[maxn], p[maxn];
int64_t f[maxn][maxn], g[maxn], binom[maxn][maxn];

void dfs(int p) {
    f[p][1] = siz[p] = 1;
    for (auto x : graph[p]) {
        dfs(x);
        for (int i = 1; i <= siz[p]; i++) g[i] = f[p][i], f[p][i] = 0;
        for (int i = 1; i <= siz[p] + siz[x]; i++)
            for (int j = 1; j <= siz[p]; j++)
                for (int k = max(1, i - j); k <= siz[x]; k++)
                    f[p][i] =
                        (f[p][i] + g[j] * f[x][k] % mod * binom[i - 1][j - 1] % mod * binom[j - 1][k + j - i]) % mod;
        siz[p] += siz[x];
    }
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    US.init(n);
    for (int i = 1; i <= m; i++) {
        int x, y;
        char c;
        cin >> x >> c >> y;
        if (c == '<')
            edges.emplace_back(x, y);
        else
            US.merge(x, y);
    }
    for (int i = 1; i <= n; i++) p[i] = US.getfa(i);
    for (auto i : edges) {
        int x = p[i.first], y = p[i.second];
        if (US.merge(y, x))
            graph[x].push_back(y);
        else
            return cout << 0 << '\n', void();
    }
    for (int i = 1; i <= n; i++)
        if (US.getfa(i) == i) graph[0].push_back(i);
    dfs(0);
    int64_t ans = 0;
    for (int i = 1; i <= n + 1; i++) ans = (ans + f[0][i]) % mod;
    cout << ans << '\n';
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}