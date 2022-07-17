/**
 * @file 1707B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-16
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

void solve(void) {
    int n, cnt = 0;
    cin >> n;
    vector<int> a;
    for (int i = 1, t; i <= n; i++) {
        cin >> t;
        if (t)
            a.push_back(t);
        else
            cnt++;
    }
    for (int i = 1; i < n && !a.empty(); i++) {
        vector<int> b;
        if (cnt) b.push_back(a.front()), cnt--;
        for (int j = 0; j + 1 < (int)a.size(); j++)
            if (a[j + 1] - a[j])
                b.push_back(a[j + 1] - a[j]);
            else
                cnt++;
        sort(b.begin(), b.end()), a = b;
    }
    cout << (a.empty() ? 0 : a[0]) << endl;
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