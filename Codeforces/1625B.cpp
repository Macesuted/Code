/**
 * @file 1625B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int a[150005];
map<int, vector<int>> rec;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], rec[a[i]].push_back(i);
    int ans = -1;
    for (auto i : rec)
        for (auto j = i.second.begin(); j + 1 != i.second.end(); j++)
            ans = max(ans, *j + (n - *(j + 1)));
    cout << ans << endl;
    rec.clear();
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
