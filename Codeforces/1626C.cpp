/**
 * @file 1626C.cpp
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

#define maxn 105

typedef pair<int, int> pii;

pii a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first;
    for (int i = 1; i <= n; i++) cin >> a[i].second;
    long long ans = 0;
    int last = a[n].first, lasth = a[n].second;
    for (int i = n; i; i--) {
        if (last - lasth + 1 <= a[i].first)
            lasth = max(lasth, a[i].second + last - a[i].first);
        else
            ans += (1LL + lasth) * lasth / 2, last = a[i].first, lasth = a[i].second;
    }
    cout << ans + (1LL + lasth) * lasth / 2 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
