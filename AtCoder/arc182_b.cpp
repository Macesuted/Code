/**
 * @file arc182_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

void solve(void) {
    int n, k;
    cin >> n >> k;
    vector<int> ans;
    ans.push_back(1);
    for (int d = 1; d < k; d++) {
        for (auto &i : ans) i <<= 1;
        int cnt = ans.size();
        for (int i = 0; i < cnt; i++)
            if ((int)ans.size() < n) ans.push_back(ans[i] + 1);
    }
    while ((int)ans.size() < n) ans.push_back(1);
    sort(ans.begin(), ans.end());
    for (auto i : ans) cout << i << ' ';
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