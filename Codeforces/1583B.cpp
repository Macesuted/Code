#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

bool vis[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        vis[b] = true;
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            for (int j = 1; j <= n; j++)
                if (i != j) cout << i << ' ' << j << endl;
            return;
        }
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}