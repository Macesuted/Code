/**
 * @file 64.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int a[maxn], p[maxn];
vector<pii> ans;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (a[i] == i) continue;
        int x = p[i], y = p[p[i]];
        ans.emplace_back(x, y), swap(p[a[a[x]]], p[a[a[y]]]), swap(a[a[x]], a[a[y]]);
    }
    cout << ans.size() << endl;
    for (auto i : ans) cout << i.first << ' ' << i.second << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("swap.in", "r", stdin), freopen("swap.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}