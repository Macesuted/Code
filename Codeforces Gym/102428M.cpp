/**
 * @file 102428M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

int s[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> s[i];

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j + 1 <= n && s[j + 1] - s[j] <= m) j++;
        ans = max(ans, j - i + 1);
    }
    cout << ans << endl;

    return 0;
}