#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 2005
#define mod1 1000000007
#define mod2 1000000009
#define base 19560929

vector<vector<int>> graph;

int c[maxn], f[maxn];
int cnt[maxn], cntt = 0;

void dfs(int p, int pre = -1) {
    if (cnt[c[p]] == 0) cntt++;
    cnt[c[p]]++;
    f[p] = cntt;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p);
    cnt[c[p]]--;
    if (cnt[c[p]] == 0) cntt--;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        graph[f].push_back(i), graph[i].push_back(f);
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        dfs(i);
        int ans = 0, p = 1;
        for (int j = 1; j <= n; j++)
            ans = (ans + p * f[j]) % mod1, p = p * base % mod1;
        cout << ans << ' ';
        ans = 0, p = 1;
        for (int j = 1; j <= n; j++)
            ans = (ans + p * f[j]) % mod2, p = p * base % mod2;
        cout << ans << endl;
    }
    graph.clear();
    return;
}

bool mem2;

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}