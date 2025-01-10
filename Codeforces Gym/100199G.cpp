/**
 * @file 100199G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

#define maxn 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class FenwickTree {
   private:
    pii tree[maxn];

   public:
    void insert(int p, pii v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] = max(tree[i], v);
        return;
    }
    pii query(int p) {
        pii ans = {0, 0};
        for (int i = p; i; i -= i & -i) ans = max(ans, tree[i]);
        return ans;
    }
} FT;

tiii a[maxn];
int b[maxn], pre[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]), get<2>(a[i]) = i, b[i] = get<1>(a[i]);
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) get<1>(a[i]) = lower_bound(b + 1, b + n + 1, get<1>(a[i])) - b;
    for (int i = 1, j; i <= n; i = j + 1) {
        j = i;
        while (j < n && get<0>(a[j + 1]) == get<0>(a[j])) j++;
        for (int t = j; t >= i; t--) {
            auto [v, p] = FT.query(get<1>(a[t]) - 1);
            pre[t] = p, FT.insert(get<1>(a[t]), {v + 1, t});
        }
    }
    auto [v, p] = FT.query(maxn - 1);
    cout << v << endl;
    vector<int> ans;
    while (p) ans.push_back(get<2>(a[p])), p = pre[p];
    sort(ans.begin(), ans.end());
    for (auto x : ans) cout << x << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("people.in", "r", stdin), freopen("people.out", "w", stdout);
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