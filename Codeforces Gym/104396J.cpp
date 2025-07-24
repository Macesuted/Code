/**
 * @file 104396J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 55

string a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            for (size_t x = 0; x < a[i].size(); x++)
                for (size_t y = 0; y < a[j].size(); y++) {
                    int len = 1;
                    while (x + len <= a[i].size() && y + len <= a[j].size() && a[i][x + len - 1] == a[j][y + len - 1]) len++;
                    ans = max(ans, len - 1);
                }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}