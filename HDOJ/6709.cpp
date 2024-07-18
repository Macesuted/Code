/**
 * @file 6709.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cstdio>
using namespace std;

#define maxn 100005

int a[maxn];

void solve(void) {
    int n, k;
    scanf("%d%d", &n, &k);
    long long ans = k, tot = n - 1;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), ans += a[i], tot -= a[i] / k, a[i] = k - a[i] % k;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n && tot > 0; i++) tot--, ans += a[i];
    while (tot > 0) tot--, ans += k;
    printf("%lld\n", ans);
    return;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) solve();
    return 0;
}