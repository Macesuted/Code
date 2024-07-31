/**
 * @file 81600E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 100005

int a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] > b[i])
            ans++;
        else if (a[i] == b[i])
            cnt++;
    cout << ans + ((cnt + 1) / 2) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}