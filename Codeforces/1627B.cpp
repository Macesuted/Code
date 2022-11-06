/**
 * @file 1627B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

int dist(int r1, int c1, int r2, int c2) { return abs(r1 - r2) + abs(c1 - c2); }

void solve(void) {
    int n, m;
    cin >> n >> m;
    static vector<int> a;
    a.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a.push_back(max({dist(i, j, 1, 1), dist(i, j, 1, m), dist(i, j, n, 1), dist(i, j, n, m)}));
    sort(a.begin(), a.end());
    for (auto i : a) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
