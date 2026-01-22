/**
 * @file 14411.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005
#define B 2000
#define maxsqrtn 205

using tiiii = tuple<int, int, int, int>;

class FenwickTree {
   private:
    int a[maxn];

   public:
    void add(int p, int v) {
        for (int i = p + 1; i < maxn; i += i & -i) a[i] += v;
        return;
    }
    int query(int p) {
        int ans = 0;
        for (int i = p + 1; i; i -= i & -i) ans += a[i];
        return ans;
    }
};

tiiii ques[maxn];
vector<int> chld[maxn];
int v[maxn << 1], ans[maxn];
FenwickTree FT[maxsqrtn];

void solve(void) {
    int q;
    cin >> q;
    for (int i = 1, l, r, k; i <= q; i++) cin >> l >> r >> k, ques[i] = {l, r, k, i};

    sort(ques + 1, ques + q + 1, [&](const tiiii& x, const tiiii& y) { return get<1>(x) < get<1>(y); });

    for (int i = 0; i < (maxn << 1); i++) FT[i / B].add(v[i] = 0, +1);

    int R = 0;
    for (int i = 1; i <= q; i++) {
        auto [l, r, k, id] = ques[i];
        k++;

        while (R < r) {
            R++;
            for (auto p : chld[R]) {
                FT[p / B].add(v[p], -1);
                v[p] = R;
                FT[p / B].add(v[p], +1);
            }
        }

        int x = -1, nxt, cur = 0;
        while (cur + (nxt = FT[(x + 1) / B].query(l - 1)) < k) x += B, cur += nxt;

        while (cur < k) cur += v[++x] < l;

        ans[id] = x;
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int i = 1; i < maxn; i++)
        for (int j = i; j < maxn; j += i) chld[j].push_back(i);

    int _ = 1;
    while (_--) solve();

    return 0;
}
