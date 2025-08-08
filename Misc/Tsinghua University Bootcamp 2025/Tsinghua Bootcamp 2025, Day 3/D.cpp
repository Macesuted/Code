#include <bits/stdc++.h>
#define eb emplace_back
#define fi first
#define se second
using namespace std;

int dp[10010][10010];
pair<int, int> q[100010];
int hh, tt;
void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int len = 1; len <= n; len++) {
        hh = 0, tt = -1;
        int st = n - len + 1;
        for (int l = n; l >= 1; l--) {
            int r = l + len - 1;

            if (l > st) {
                if (len <= m) continue;

                while (hh <= tt && q[hh].se > r - len + m + 1) ++hh;
                while (hh <= tt && q[hh].se > r - len + m) ++hh;
                int add = dp[len - m][l];
                while (hh <= tt && q[tt].fi >= add) --tt;
                q[++tt] = {add, l};

                continue;
            }

            if (len <= m) {
                dp[len][l] = max(a[l], a[r]);
                continue;
            }

            while (hh <= tt && q[hh].se > r - len + m + 1) ++hh;
            if (hh <= tt) dp[len][l] = max(dp[len][l], a[l] + q[hh].fi);
            while (hh <= tt && q[hh].se > r - len + m) ++hh;
            int add = dp[len - m][l];
            while (hh <= tt && q[tt].fi >= add) --tt;
            q[++tt] = {add, l};
            if (hh <= tt) dp[len][l] = max(dp[len][l], a[r] + q[hh].fi);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (i > n)
            cout << "0 ";
        else {
            int len = n - i + 1;
            int ans = dp[len][1];
            for (int j = 1; j + len - 1 <= n; j++) {
                ans = min(ans, dp[len][j]);
            }
            cout << ans << ' ';
        }
    }
    cout << '\n';

    return;
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int _ = 1;
    while (_--) solve();

    return 0;
}