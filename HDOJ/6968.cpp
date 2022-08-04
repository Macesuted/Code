#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 55
#define maxt 505
#define maxm 15005

typedef pair<int, int> pii;

long long f[maxn][maxt][4], g[maxt];

map<string, int> rec;
vector<pii> a[maxn];
int cnt = 0;

void solve(void) {
    int n;
    cin >> n;
    rec.clear(), cnt = 0;
    for (int i = 1; i <= n; i++) a[i].clear();
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        rec[s] = ++cnt;
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        int p = rec[s], x, y;
        cin >> x >> y;
        a[p].emplace_back(y, x);
    }
    int T, P;
    cin >> T >> P;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= T; j++)
            for (int k = 0; k <= P; k++) f[i][j][k] = numeric_limits<int>::min() / 2;
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= T; k++) g[k] = numeric_limits<int>::min() / 2;
        g[0] = 0;
        for (auto j : a[i])
            for (int k = T; k >= j.first; k--) g[k] = max(g[k], g[k - j.first] + j.second);
        for (int k = 0; k <= T; k++) g[k] = min(g[k], 100LL);
        for (int k = 0; k <= T; k++)
            for (int j = T; j >= k; j--)
                for (int t = 0; t <= P; t++) {
                    if (t == 0 && g[k] < 60) continue;
                    f[i][j][t] = max(f[i][j][t], f[i - 1][j - k][t - (g[k] < 60)] + g[k]);
                }
    }
    int ans = numeric_limits<int>::min();
    for (int j = 0; j <= T; j++)
        for (int k = 0; k <= P; k++) ans = max(ans, f[n][j][k]);
    cout << max(-1LL, ans) << endl;
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