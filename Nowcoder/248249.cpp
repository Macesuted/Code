/**
 * @file 248249.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-16
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

#define maxn 300005

class FenwickTree {
   private:
    int a[maxn];

   public:
    void update(int p, int v) {
        for (int i = p + 1; i < maxn; i += i & -i) a[i] += v;
        return;
    }
    int query(int p) {
        int sum = 0;
        for (int i = p + 1; i; i -= i & -i) sum += a[i];
        return sum;
    }
} FT;

int a[maxn];

void solve(void) {
    int n, q, W;
    cin >> n >> q >> W;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], FT.update(a[i], 1), ans += FT.query(max(-1, W - a[i]));
    while (q--) {
        int p, x;
        cin >> p >> x;
        ans -= FT.query(max(-1, W - a[p])), FT.update(a[p], -1);
        FT.update(a[p] = x, 1), ans += FT.query(max(-1, W - a[p]));
        cout << ans << endl;
    }
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