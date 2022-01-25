/**
 * @file 1626D.cpp
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

#define maxn 200005
#define maxlgn 20

int a[maxn], t[maxn], l[maxlgn], r[maxlgn];

int near(int x) {
    int v = 1;
    while (v < x) v <<= 1;
    return v - x;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) a[i] = 0;
    for (int i = 1; i <= n; i++) cin >> t[i], a[t[i]]++;
    if (n == 1) return cout << 2 << endl, void();
    sort(t + 1, t + n + 1);
    for (int i = 0, j = 1, sum = 0; i < maxlgn; i++) {
        int lim = 1 << i;
        while (j <= n && sum + a[j] <= lim) sum += a[j++];
        l[i] = sum;
    }
    for (int i = 0, j = n, sum = 0; i < maxlgn; i++) {
        int lim = 1 << i;
        while (j && sum + a[j] <= lim) sum += a[j--];
        r[i] = sum;
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < maxlgn; i++)
        for (int j = 0; j < maxlgn; j++)
            if (l[i] == 0 || r[j] == 0 || t[l[i]] < t[n - r[j] + 1])
                ans = min(ans, (1 << i) - l[i] + (1 << j) - r[j] + near(n - l[i] - r[j]));
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
