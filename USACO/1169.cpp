/**
 * @file 1169.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    long long ans = 0;
    for (int i = 1; i < n; i++)
        if (a[i] != a[i + 1]) {
            int d = abs(a[i] - a[i + 1]);
            if (a[i] > a[i + 1]) {
                if (i & 1) return cout << -1 << endl, void();
                ans += 1LL * i * d;
                a[i] -= d;
                if (a[i] < 0) return cout << -1 << endl, void();
            } else {
                if (i + 2 > n) return cout << -1 << endl, void();
                a[i + 1] -= d, a[i + 2] -= d;
                if (a[i + 1] < 0 || a[i + 2] < 0) return cout << -1 << endl, void();
                ans += 2 * d;
            }
        }
    cout << ans << endl;
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
