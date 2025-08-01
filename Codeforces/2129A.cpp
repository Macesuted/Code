/**
 * @file 2129A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-31
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

#define maxn 3005

using tiii = tuple<int, int, int>;

tiii a[maxn];
int ans[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]), get<2>(a[i]) = i;
    sort(a + 1, a + n + 1);
    vector<int> ans;
    for (int i = 1, j; i <= n; i = j + 1) {
        j = i;
        while (j + 1 <= n && get<0>(a[i]) == get<0>(a[j + 1])) j++;
        ans.push_back(get<2>(a[j]));
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
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