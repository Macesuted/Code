/**
 * @file 387E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int getSum(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += tree[i];
        return ans;
    }
} FT;

int a[maxn], pos[maxn], lef[maxn], rig[maxn];
bool blk[maxn], vis[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
    for (int i = 1, x; i <= k; i++) cin >> x, blk[pos[x]] = true;

    {
        vector<pii> S;
        S.emplace_back(INT_MIN, 0);
        for (int i = 1; i <= n; i++)
            if (blk[i]) {
                while (S.back().first > a[i]) S.pop_back();
                S.emplace_back(a[i], i);
            } else
                lef[i] = (lower_bound(S.begin(), S.end(), pii{a[i], 0}) - 1)->second + 1;
    }
    {
        vector<pii> S;
        S.emplace_back(INT_MIN, n + 1);
        for (int i = n; i; i--)
            if (blk[i]) {
                while (S.back().first > a[i]) S.pop_back();
                S.emplace_back(a[i], i);
            } else
                rig[i] = (lower_bound(S.begin(), S.end(), pii{a[i], 0}) - 1)->second - 1;
    }

    for (int i = 1; i <= n; i++) FT.add(i, 1);

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        int p = pos[i];
        if (blk[p]) continue;
        ans += FT.getSum(rig[p]) - FT.getSum(lef[p] - 1);
        FT.add(p, -1);
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