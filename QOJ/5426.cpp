/**
 * @file 5426.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 4005

using pii = pair<int, int>;

pii a[maxn];
int f[maxn];

vector<int> graph[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second, a[i + n] = a[i];

    int s = 2;
    while (a[s - 1].second == a[s].second) s++;

    int ans = 0;
    for (int i = s, j; i < s + n; i = j + 1) {
        j = i;
        while (j + 1 < s + n && a[j].second == a[j + 1].second) j++;
        pii pl = a[i - 1], pr = a[j + 1];
        pii dl = {pl.first - a[i].first, pl.second - a[i].second}, dr = {pr.first - a[j].first, pr.second - a[j].second};
        if (dl.second < 0 || dr.second < 0) continue;
        if (a[i].first > a[j].first) continue;
        if ((int64_t)dr.first * dl.second - (int64_t)dr.second * dl.first <= 0 && i == j) continue;
        ans++;
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
