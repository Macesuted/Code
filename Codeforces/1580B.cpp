/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/cf1580b
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 105

typedef pair<int, int> pii;

int f[maxn][maxn][maxn];
int C[maxn][maxn], fac[maxn];

int n, m, k, mod;

int dp(int len, int up, int cnt) {
    if (!len) return cnt == 0;
    if (up == 1) return cnt == 1 ? fac[len] : 0;
    if ((cnt - 1) * 2 > len) return 0;
    if (f[len][up][cnt] >= 0) return f[len][up][cnt];
    int answer = 0;
    for (int mid = 0; mid < len; mid++)
        for (int t = 0; t <= cnt; t++)
            answer = (answer +
                      dp(mid, up - 1, t) * dp(len - mid - 1, up - 1, cnt - t) % mod * C[len - 1][mid]) %
                     mod;
    return f[len][up][cnt] = answer;
}

void work(void) {
    memset(f, -1, sizeof(f));
    cin >> n >> m >> k >> mod;
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    cout << dp(n, m, k) << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}
