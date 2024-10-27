/**
 * @file 9529.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int64_t cnt[maxn], val[maxn], tot = 0, totVal = 0;

void add(int p, int64_t v) {
    tot += v, totVal += v * p;
    for (int i = p; i < maxn; i += i & -i) cnt[i] += v, val[i] += v * p;
    return;
}
int64_t sum(int p) {
    int64_t ans = tot;
    for (int i = p - 1; i; i -= i & -i) ans -= cnt[i];
    return ans;
}
int64_t getAns(int p) {
    int64_t ans = totVal;
    for (int i = p - 1; i; i -= i & -i) ans -= val[i];
    return ans;
}
int64_t solve(int64_t m) {
    int l = 1, r = 1e6 + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (sum(mid) >= m ? l : r) = mid;
    }
    return getAns(l) - (sum(l) - m) * l;
}

int w[maxn], l[maxn], r[maxn];

void solve(void) {
    int n;
    int64_t m, ans = 0, cur = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i] >> l[i] >> r[i], m -= l[i], cur += (int64_t)l[i] * w[i], add(w[i], r[i] - l[i]);
    ans = cur + solve(m);
    for (int i = 1; i <= n; i++) {
        m += l[i], cur -= (int64_t)l[i] * w[i], add(w[i], l[i] - r[i]);
        add(w[i], m);
        ans = max(ans, cur + solve(m));
        add(w[i], -m);
        m -= l[i], cur += (int64_t)l[i] * w[i], add(w[i], r[i] - l[i]);
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}