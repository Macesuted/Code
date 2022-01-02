/**
 * @file 1616C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 75

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (n == 1) return cout << 0 << endl, void();
    int ans = 0x3f3f3f3f;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++) {
            int pu = a[j] - a[i], pd = double(j - i), pg = __gcd(pu, pd);
            pu /= pg, pd /= pg;
            int cnt = 0;
            for (int k = 1; k <= n; k++)
                if (abs(i - k) % pd != 0 || a[i] + (k - i) / pd * pu != a[k])
                    cnt++;
            ans = min(ans, cnt);
        }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
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
