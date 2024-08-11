/**
 * @file abc366_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
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

#define maxn 105

string a[maxn];

void solve(void) {
    int n, m = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], m = max(m, (int)a[i].size());
    for (int i = 0; i < m; i++) {
        string t;
        for (int j = n; j; j--)
            if ((int)a[j].size() <= i)
                t.push_back('*');
            else
                t.push_back(a[j][i]);
        while (t.back() == '*') t.pop_back();
        cout << t << endl;
    }
    return;
}

bool mem2;

int main() {
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