/**
 * @file A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-20
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

#define maxn 1000005

int64_t a[maxn], cnt[2][10];

bool chk(int m1, int m2, int64_t cnt[]) {
    if (m1 < cnt[1]) return false;
    m1 -= cnt[1];
    if (m2 <= cnt[2]) return 2 * (cnt[2] - m2) + cnt[4] <= m1;
    m2 -= cnt[2];
    if (m2 <= 2 * cnt[4]) return cnt[4] - m2 / 2 + (m2 % 2) <= m1;
    m2 -= cnt[4] * 2;
    if (m2 <= 3 * cnt[6]) return m2 % 3 <= m1;
    m2 -= cnt[6] * 3;
    if (m2 <= cnt[3]) return m2 <= m1;
    return false;
}

void solve(void) {
    int m, k;
    cin >> m >> k;
    for (int i = 1; i <= m; i++) cin >> a[i];
    int n = m >> 1;
    for (int i = 1; i <= n; i++) a[i] -= a[m - i + 1];
    a[n + 1] = a[0] = 0;
    for (int i = n + 1; i; i--) a[i] -= a[i - 1];
    n++;
    if (k == 1) {
        int64_t ans = 0;
        for (int i = 1; i <= n; i++)
            if (a[i] > 0) ans += a[i];
        cout << ans << endl;
        return;
    } else if (k == 2) {
        int64_t sum = 0, cnt[2] = {0, 0};
        for (int i = 1; i <= n; i++)
            if (a[i] > 0)
                sum += a[i], cnt[0] += a[i] / 2;
            else
                cnt[1] += -a[i] / 2;
        cout << sum - min(cnt[0], cnt[1]) << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!a[i]) continue;
        int t = a[i] > 0;
        a[i] = abs(a[i]);
        cnt[t][6] += (a[i] - 2) / 6, a[i] = (a[i] - 2) % 6 + 2;
        if (a[i] == 5 || a[i] == 7) cnt[t][3]++, a[i] -= 3;
        cnt[t][a[i]]++;
    }
    int64_t tot = 0, ans = INT64_MAX;
    for (int i = 1; i <= 6; i++) tot += i * cnt[0][i];
    for (int m1 = cnt[0][1] + 2 * cnt[0][2] + 3 * cnt[0][3] + 4 * cnt[0][4] + 6; ~m1; m1--)
        for (int m2 = cnt[0][2] + cnt[0][3] + 2 * cnt[0][4] + 3; ~m2; m2--) {
            if (m1 + m2 * 2 > tot || (tot - m1 - m2 * 2) % 3) continue;
            int64_t m3 = (tot - m1 - m2 * 2) / 3;
            if (m1 + m2 + m3 >= ans) continue;
            if (chk(m1, m2, cnt[0]) && chk(m1, m2, cnt[1])) ans = m1 + m2 + m3;
        }
    cout << ans << endl;
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