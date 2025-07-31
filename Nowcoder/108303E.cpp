/**
 * @file 108303E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

bool mem1;

class Block {
   private:
    int64_t a[maxn], sum[500];
    int bl[500], br[500], bel[maxn];
    const int B = 320;

   public:
    void resize(int n) {
        bl[0] = br[0] = 0;
        int Bcnt = 0;
        while (br[Bcnt] < n) Bcnt++, bl[Bcnt] = br[Bcnt - 1] + 1, br[Bcnt] = br[Bcnt - 1] + B;
        for (int t = 1; t <= Bcnt; t++)
            for (int i = bl[t]; i <= br[t]; i++) bel[i] = t;
        return;
    }
    void update(int p, int64_t x) { return a[p] += x, sum[bel[p]] += x, void(); }
    int64_t query(int l, int r) {
        int64_t ans = 0;
        int L = bel[l], R = bel[r];
        if (L == R) {
            for (int i = l; i <= r; i++) ans += a[i];
            return ans;
        }
        for (int i = l; i <= br[L]; i++) ans += a[i];
        for (int i = L + 1; i < R; i++) ans += sum[i];
        for (int i = bl[R]; i <= r; i++) ans += a[i];
        return ans;
    }
} BLK;

int p[maxn], rp[maxn], cnt[maxn], rc[maxn], bl[maxn], br[maxn], bel[maxn];
short rec[205][maxn];
int64_t laz[205];

bool mem2;

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i], cnt[p[i]]++;

    for (int i = 2; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; i++) rc[i] = cnt[i - 1] + 1;

    for (int i = 1; i <= n; i++) rp[p[i] = rc[p[i]]++] = i;

    int B = 500, Bcnt = 0;
    while (br[Bcnt] < n) Bcnt++, bl[Bcnt] = br[Bcnt - 1] + 1, br[Bcnt] = min(n, br[Bcnt - 1] + B);
    for (int t = 1; t <= Bcnt; t++) {
        for (int i = bl[t]; i <= br[t]; i++) bel[i] = t, rec[t][rp[i]]++;
        for (int i = 1; i <= n; i++) rec[t][i] += rec[t][i - 1];
    }

    BLK.resize(n);

    int64_t lstans = 0;
    while (q--) {
        int64_t opt, l, r;
        cin >> opt >> l >> r, l ^= lstans, r ^= lstans;
        if (opt == 1) {
            int64_t x;
            cin >> x, x ^= lstans;
            l = cnt[l - 1] + 1, r = cnt[r];
            if (l > r) continue;

            int L = bel[l], R = bel[r];
            if (L == R) {
                for (int i = l; i <= r; i++) BLK.update(rp[i], x);
                continue;
            }

            for (int i = l; i <= br[L]; i++) BLK.update(rp[i], x);
            for (int i = L + 1; i < R; i++) laz[i] += x;
            for (int i = bl[R]; i <= r; i++) BLK.update(rp[i], x);
        } else {
            int64_t ans = BLK.query(l, r);
            for (int t = 1; t <= Bcnt; t++) ans += (rec[t][r] - rec[t][l - 1]) * laz[t];
            cout << (lstans = ans) << endl;
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
