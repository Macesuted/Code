/**
 * @file 1352D.cpp
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

#define maxn 1005

int x[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    int cnt = 0, a = 0, b = 0, l = 1, r = n, opt = 0, last = 0;
    while (l <= r) {
        opt ^= 1, cnt++;
        if (opt) {
            int t = max(last + 1, x[l]), sum = 0;
            while (l <= r && sum < t) sum += x[l++];
            a += sum, last = sum;
        } else {
            int t = max(last + 1, x[r]), sum = 0;
            while (l <= r && sum < t) sum += x[r--];
            b += sum, last = sum;
        }
    }
    cout << cnt << ' ' << a << ' ' << b << endl;
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
