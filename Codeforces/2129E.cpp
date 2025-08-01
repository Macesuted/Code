/**
 * @file 2129E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-01
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

#define maxn 300005

class Block {
   private:
    vector<int> cntL, cnt;
    int n, B;

   public:
    void resize(int _n) { return n = _n, B = max(1., sqrt(n)), cntL.resize(n / B + 1), cnt.resize(n + 1); }

    void insert(int v) { return cntL[v / B]++, cnt[v]++, void(); }
    void erase(int v) { return cntL[v / B]--, cnt[v]--, void(); }
    int getRank(int k) {
        int x = 0;
        while (cntL[x / B] < k) k -= cntL[x / B], x += B;
        while (cnt[x] < k) k -= cnt[x], x++;
        return x;
    }
};

using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;

int ans[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<tiii> a;
    vector<int> deg(n + 1, 0), predeg(n + 1, 0);
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        a.emplace_back(x, y, i), a.emplace_back(y, x, i), deg[x]++, deg[y]++;
    }
    sort(a.begin(), a.end());
    for (int i = 1; i <= n; i++) predeg[i] = predeg[i - 1] + deg[i];

    int B = sqrt(a.size());

    int q;
    cin >> q;

    vector<tiiii> ques;
    for (int i = 1, l, r, k; i <= q; i++) cin >> l >> r >> k, ques.emplace_back(l, r, k, i);
    sort(ques.begin(), ques.end(), [&](const tiiii& a, const tiiii& b) -> bool {
        int al = predeg[get<0>(a) - 1] / B, bl = predeg[get<0>(b) - 1] / B;
        return al == bl ? ((get<1>(a) < get<1>(b)) ^ (al & 1)) : al < bl;
    });

    int L = 0, R = -1;
    Block blk;
    blk.resize(n * 2);
    vector<int> val(n + 1, 0), vis(m + 1, 0);

    for (int i = 1; i <= n; i++) blk.insert(0);

    auto insert = [&](int x) -> void {
        auto [u, v, id] = a[x];
        if (!vis[id]++) return;
        blk.erase(val[u]), blk.insert(val[u] ^= v);
        blk.erase(val[v]), blk.insert(val[v] ^= u);
        return;
    };
    auto erase = [&](int x) -> void {
        auto [u, v, id] = a[x];
        if (!--vis[id]) return;
        blk.erase(val[u]), blk.insert(val[u] ^= v);
        blk.erase(val[v]), blk.insert(val[v] ^= u);
        return;
    };

    for (auto [l, r, k, id] : ques) {
        while (L - 1 >= 0 && get<0>(a[L - 1]) >= l) insert(--L);
        while (R + 1 < (int)a.size() && get<0>(a[R + 1]) <= r) insert(++R);
        while (L < (int)a.size() && get<0>(a[L]) < l) erase(L++);
        while (R >= 0 && get<0>(a[R]) > r) erase(R--);
        ans[id] = blk.getRank(n - (r - l + 1) + k);
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}