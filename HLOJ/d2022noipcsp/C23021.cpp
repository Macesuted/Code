/**
 * @file C23021.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-08
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

int64_t c;
int n, a[maxn], b[maxn];
bool avai[maxn];

int64_t check(double lim) {
    for (int i = 1; i <= n; i++) avai[i] = (a[i] >= lim * b[i]);
    int64_t sA = 0, sB = c, ans = 0;
    for (int l = 1, r = 0; l <= n; l++) {
        while (r < n && (!avai[r + 1] || sA + a[r + 1] <= lim * (sB + b[r + 1])))
            if (avai[++r]) sA += a[r], sB += b[r];
        ans += r - l + 1;
        if (avai[l]) sA -= a[l], sB -= b[l];
    }
    return ans;
}

void solve(void) {
    int64_t k;
    cin >> n >> k >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    double l = 0, r = 1;
    while (fabs(r - l) > 1e-8) {
        double mid = (l + r) / 2;
        (check(mid) < k ? l : r) = mid;
    }
    cout << setprecision(10) << l << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("fraction.in", "r", stdin), freopen("fraction.out", "w", stdout);
#endif
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