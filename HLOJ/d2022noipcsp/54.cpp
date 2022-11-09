/**
 * @file 54.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
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

#define maxn 200005
#define maxv 1000005
#define maxsqrtn 500
#define mod 20011

class HashList {
   private:
    pair<uint64_t, int> rec[mod];
    int cac[maxsqrtn], cnt;

    int Mod(int x) { return x >= mod ? x - mod : x; }

   public:
    HashList(void) { cnt = 0; }
    void add(uint64_t key, int val) {
        int pos = key % mod;
        while (rec[pos].first && rec[pos].first != key) pos = Mod(pos + 1);
        rec[pos] = {key, rec[pos].second + val}, cac[cnt++] = pos;
        return;
    }
    void clear(void) {
        for (int i = 0; i < cnt; i++) rec[cac[i]] = {0, 0};
        cnt = 0;
        return;
    }
    int query(uint64_t key) {
        int pos = key % mod;
        while (rec[pos].first && rec[pos].first != key) pos = Mod(pos + 1);
        if (rec[pos].first != key) return 0;
        return rec[pos].second;
    }
};

int a[maxn], bel[maxn], L[maxsqrtn], R[maxsqrtn], rig[maxn], pos[maxv];
uint64_t val[maxv], pre[maxn], laz[maxsqrtn];
HashList blk[maxsqrtn];

void solve(void) {
    int n, B, blkcnt;
    cin >> n, B = sqrt(n), blkcnt = n / B;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (pos[a[i]]) pre[i] = val[a[i]];
        pos[a[i]] = i;
    }
    memset(pos, 0, sizeof(pos));
    for (int i = n; i; i--) rig[i] = pos[a[i]], pos[a[i]] = i;
    for (int i = 1; i <= n; i++) pre[i] ^= pre[i - 1];
    for (int i = 1; i <= blkcnt; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + B;
    if (R[blkcnt] < n) L[blkcnt + 1] = R[blkcnt] + 1, R[++blkcnt] = n;
    for (int i = 1; i <= blkcnt; i++)
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i, blk[i].add(pre[j], 1);
    int64_t ans = 0;
    for (int l = 1; l <= n; l++) {
        int bl = bel[l];
        for (int i = l; i <= R[bl]; i++) ans += (pre[i] == laz[bl]);
        for (int i = bl + 1; i <= blkcnt; i++) ans += blk[i].query(laz[i]);
        if (rig[l]) {
            int p = rig[l], bp = bel[p];
            for (int i = p; i <= R[bp]; i++) pre[i] ^= val[a[l]];
            blk[bp].clear();
            for (int i = L[bp]; i <= R[bp]; i++) blk[bp].add(pre[i], 1);
            for (int i = bp + 1; i <= blkcnt; i++) laz[i] ^= val[a[l]];
        }
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("odd.in", "r", stdin), freopen("odd.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    mt19937_64 rnd(114514);
    for (int i = 0; i < maxv; i++) val[i] = rnd();

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}