/**
 * @file 268.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int query(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int n, a[maxn], t[maxn];

int64_t check(int64_t lim) {
    int64_t tot = 0, cnt = 0;
    int l = 1;
    for (int r = 1; r <= n; r++) {
        cnt += r - l - FT.query(a[r]), FT.add(a[r], +1);
        while (cnt > lim) cnt -= FT.query(a[l] - 1), FT.add(a[l++], -1);
        tot += r - l + 1;
    }
    for (int i = l; i <= n; i++) FT.add(a[i], -1);
    return tot;
}

void solve(void) {
    int64_t k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], t[i] = a[i];
    sort(t + 1, t + n + 1);
    int tn = unique(t + 1, t + n + 1) - t - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + tn + 1, a[i]) - t;
    int64_t l = 0, r = 1e18;
    if (check(0) >= k) return cout << 0 << endl, void();
    while (l + 1 < r) {
        int64_t mid = (l + r) / 2;
        (check(mid) < k ? l : r) = mid;
    }
    cout << r << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}