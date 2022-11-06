/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define maxn 200005
#define maxlgn 20

typedef pair<int, int> pii;

vector<vector<int> > graph;
long long f[maxn];
int siz[maxn], fa[maxn][maxlgn], dep[maxn];

void dfs(int p, int pre) {
    dep[p] = dep[pre] + 1;
    fa[p][0] = pre;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    siz[p] = 1;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            dfs(*i, p);
            siz[p] += siz[*i];
        }
    return;
}
int dist(int x, int y) {
    if (x == y) return 0;
    int ans = 0;
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i], ans += 1 << i;
    if (x == y) return ans;
    for (register int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i], ans += 1 << (i + 1);
    return ans + 2;
}
int gett(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] > dep[y]) x = fa[x][i];
    return x;
}

void work(void) {
    int n;
    cin >> n;
    graph.resize(n + 1);
    for (register int i = 1, from, to; i < n; i++) {
        cin >> from >> to;
        from++, to++;
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs(1, 0);
    f[0] = 1LL * n * (n - 1) / 2, f[1] = 0;
    for (vector<int>::iterator i = graph[1].begin(); i != graph[1].end(); i++) f[1] += 1LL * siz[*i] * (n - siz[*i] - 1);
    f[1] = f[1] / 2 + n - 1;
    int l = 1, r = 1;
    for (register int i = 2; i <= n; i++) {
        int dist1 = dist(l, i), dist2 = dist(i, r), dist3 = dist(l, r);
        if (dist1 + dist2 == dist3) {
        } else if (dist1 + dist3 == dist2)
            l = i;
        else if (dist2 + dist3 == dist1)
            r = i;
        else {
            for (register int j = i; j <= n; j++) f[i] = 0;
            break;
        }
        // cerr << "#" << l << ' ' << r << endl;
        if (l == 1)
            f[i] = 1LL * (siz[l] - siz[gett(l, r)]) * siz[r];
        else if (r == 1)
            f[i] = 1LL * siz[l] * (siz[r] - siz[gett(l, r)]);
        else
            f[i] = 1LL * siz[l] * siz[r];
    }
    f[n + 1] = 0;
    for (register int i = 0; i <= n; i++) cout << f[i] - f[i + 1] << ' ';
    // for (register int i = 0; i <= n; i++) cout << f[i] << ' ';
    cout << endl;
    graph.clear();
    for (register int i = 0; i <= n; i++) {
        siz[i] = 0, dep[i] = 0;
        for (register int j = 0; j < maxlgn; j++) fa[i][j] = 0;
        f[i] = 0;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}  // awa