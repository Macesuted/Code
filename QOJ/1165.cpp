/**
 * @file 1165.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005
#define maxd 500005

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

class SegmentTree {
   private:
    int ans[maxd << 2], laz[maxd << 2];

    void pushUp(int p) { return ans[p] = max(ans[p << 1], ans[p << 1 | 1]), void(); }

    void pushDown(int p) {
        if (!laz[p]) return;
        laz[p << 1] += laz[p], ans[p << 1] += laz[p];
        laz[p << 1 | 1] += laz[p], ans[p << 1 | 1] += laz[p];
        laz[p] = 0;
        return;
    }
    void reset(int p, int l, int r) {
        ans[p] = laz[p] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        reset(p << 1, l, mid), reset(p << 1 | 1, mid + 1, r);
        return;
    }
    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return laz[p] += v, ans[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    void reset(void) { return reset(1, 0, 500000); }
    void add(int l, int r, int v) { return add(1, 0, 500000, l, r, v); }
    int query(void) { return ans[1]; }
} SGT;

int x[maxn], y[maxn], c[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> c[i], x[i] *= 2, y[i] *= 2;

    auto chk = [&](int a) -> bool {
        map<int, vector<pii>> rec;
        vector<multiset<int>> S(k + 1);
        for (int i = 1; i <= n; i++) rec[x[i] - a].emplace_back(y[i], c[i]), rec[x[i] + a].emplace_back(y[i], -c[i]);

        SGT.reset();
        for (auto &[v, upds] : rec) {
            for (auto [p, c] : upds) {
                if (c < 0) continue;

                auto &T = S[c];
                int l = max(0, p - a), r = min(500000, p + a);
                auto it = T.lower_bound(p);
                if (it != T.end()) r = min(r, *it - a - 1);
                it = T.upper_bound(p);
                if (it != T.begin()) l = max(l, *prev(it) + a + 1);
                T.insert(p);
                if (l <= r) SGT.add(l, r, +1);
            }

            if (SGT.query() == k) return true;

            for (auto [p, c] : upds) {
                if (c > 0) continue;

                auto &T = S[-c];
                int l = max(0, p - a), r = min(500000, p + a);
                T.erase(T.find(p));
                auto it = T.lower_bound(p);
                if (it != T.end()) r = min(r, *it - a - 1);
                it = T.upper_bound(p);
                if (it != T.begin()) l = max(l, *prev(it) + a + 1);
                if (l <= r) SGT.add(l, r, -1);
            }
        }
        return false;
    };

    int l = -1, r = 2.5e5;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }

    cout << r << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}