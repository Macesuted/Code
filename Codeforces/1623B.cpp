/**
 * @file 1623B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

typedef pair<int, int> pii;

#define maxn 1005

pii a[maxn];
int ans[maxn];
set<int> S;

bool cmp(pii a, pii b) { return a.second - a.first < b.second - b.first; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1, cmp);
    S.clear();
    for (int i = 1; i <= n; i++) S.insert(i);
    for (int i = 1; i <= n; i++) {
        int p = *S.lower_bound(a[i].first);
        cout << a[i].first << ' ' << a[i].second << ' ' << p << endl, S.erase(p);
    }
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
