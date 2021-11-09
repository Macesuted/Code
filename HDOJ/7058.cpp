#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 5005
#define mod 998244353

typedef pair<int, int> pii;

pii a[maxn];
int dist[maxn];
bool vis[maxn];

inline long long Dist(pii a, pii b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    dist[1] = 0;
    int ans = 0;
    while (true) {
        int p = 0;
        for (int i = 1; i <= n; i++)
            if ((!vis[i]) && ((p == 0) || (dist[i] < dist[p])))
                p = i;
        if (p == 0) break;
        vis[p] = true;
        ans = max(ans, dist[p]);
        for (int i = 1; i <= n; i++)
            if ((!vis[i]) && dist[i] > Dist(a[p], a[i]))
                dist[i] = Dist(a[p], a[i]);
    }
    cout << ans << endl;
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
