/**
 * @file 1748C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-12
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

#define maxn 200005

int a[maxn];
int64_t pre[maxn];
map<int64_t, int> rec;
vector<int> pos;

void solve(void) {
    int n, ans = 0;
    cin >> n, pos.clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i], pre[i] = pre[i - 1] + a[i];
        if (a[i] == 0) pos.push_back(i);
    }
    pos.push_back(n + 1);
    for (int i = 1; i < pos.front(); i++) ans += (pre[i] == 0);
    for (int i = 0; i + 1 < (int)pos.size(); i++) {
        rec.clear();
        for (int j = pos[i]; j < pos[i + 1]; j++) rec[pre[j]]++;
        int maxv = 0;
        for (auto i : rec) maxv = max(maxv, i.second);
        ans += maxv;
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