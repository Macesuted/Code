/**
 * @file 102465A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

bool f[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, m, cnt = 0, ans = 0;
    cin >> n >> m;
    for (int i = 1, x; i <= m; i++) {
        cin >> x;
        for (int j = x; j <= n; j += x) {
            if (!f[j])
                cnt++;
            else
                cnt--;
            f[j] = !f[j];
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}