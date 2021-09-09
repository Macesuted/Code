/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define maxn 505
#define mod 998244353

typedef pair<int, int> pii;

int f[maxn][maxn];
pii a[maxn];
int n;

int work(int p) {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (register int i = 1; i < p; i++)
        for (register int j = 0; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (!a[i].first) {
                f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
                if (j == 0) f[i][0] = (f[i][0] + f[i - 1][0]) % mod;
            } else {
                if (a[i].second <= a[p].second) {
                    if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
                } else
                    f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            }
        }
    for (register int i = 0; i <= n; i++) f[p][i] = f[p - 1][i];
    for (register int i = p + 1; i <= n; i++)
        for (register int j = 0; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (!a[i].first)
                f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
            else {
                if (a[i].second < a[p].second) {
                    if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
                } else
                    f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            }
        }
    int ans = 0;
    for (register int i = 0; i <= n; i++) ans = (ans + f[n][i]) % mod;
    return ans * a[p].second;
}

void solve(void) {
    cin >> n;
    for (register int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (a[i].first = (c == '+')) cin >> a[i].second;
    }
    int answer = 0;
    for (register int i = 1; i <= n; i++)
        if (a[i].first) answer = (answer + work(i)) % mod;
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(3);
    int _ = 1;
    // cin >> _;
    while (_--) solve();
    return 0;
}
