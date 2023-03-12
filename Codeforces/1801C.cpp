/**
 * @file 1801C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

vector<int> a[maxn];
int p[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, s; i <= n; i++) {
        cin >> s, p[i] = i, a[i].clear();
        for (int j = 0, x, mv = 0; j < s; j++) {
            cin >> x;
            if (x > mv) mv = x, a[i].push_back(x);
        }
    }
    sort(p + 1, p + n + 1, [&](int x, int y) { return a[x].back() < a[y].back(); });
    vector<pii> f;
    f.emplace_back(0, 0);
    for (int i = 1; i <= n; i++) {
        int g = 0;
        for (int j = 0; j < (int)a[p[i]].size(); j++)
            g = max(g, (--lower_bound(f.begin(), f.end(), pii{a[p[i]][j], 0}))->second + (int)a[p[i]].size() - j);
        if (f.back().first == a[p[i]].back()) f.back().second = max(f.back().second, g);
        if (f.back().second < g) f.emplace_back(a[p[i]].back(), g);
    }
    cout << f.back().second << endl;
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