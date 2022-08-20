/**
 * @file 2873.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 300005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

pii a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + n + 1, greater<pii>());
    int64_t ans = 0;
    vector<int> cache;
    for (int i = 1; i <= n; i++) {
        if (a[i].first != a[i - 1].first)
            while (!cache.empty()) FT.add(cache.back(), +1), cache.pop_back();
        ans += min(FT.sum(a[i].second), i - 1 - (int)cache.size() - FT.sum(a[i].second)), cache.push_back(a[i].second);
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