#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;

int col[maxn][maxn];

inline int ceil(int a, int b) { return (a + b - 1) / b; }

void dfs(int l, int r, int k, int dep = 1) {
    if (l == r) return;
    int t = ceil(r - l + 1, k);
    for (int tl = l, tr = l + t - 1; tl <= r; tl = tr + 1, tr = min(tl + t - 1, r)) {
        dfs(tl, tr, k, dep + 1);
        for (int i = tl; i <= tr; i++)
            for (int j = tr + 1; j <= r; j++) col[i][j] = dep;
    }
    return;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    int ans = 0, tans = 1;
    while (tans < n) ans++, tans *= k;
    cout << ans << endl;
    dfs(1, n, k);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) cout << col[i][j] << ' ';
    cout << endl;
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}