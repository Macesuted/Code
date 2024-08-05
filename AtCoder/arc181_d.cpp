/**
 * @file arc181_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-04
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

#define maxn 200005

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void insert(int p) {
        for (int i = p; i < maxn; i += i & -i) tree[i]++;
        return;
    }
    int query(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int a[maxn], p[maxn], pos[maxn], dt[maxn];

void solve(void) {
    int n, q;
    cin >> n;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], p[i] = i - 1 - FT.query(a[i]), FT.insert(a[i]), ans += p[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> pos[i];
    for (int i = 1, j = 1; i <= n; i++) {
        while (j <= q && pos[j] < i) j++;
        if (j <= q) dt[j]--, dt[min(q + 1, j + p[i])]++;
    }
    for (int i = 1; i <= q; i++) cout << (ans += (dt[i] += dt[i - 1])) << endl;
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