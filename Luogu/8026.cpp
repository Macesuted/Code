/**
 * @file 8026.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-16
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

#define maxn 5005
#define maxk 205

typedef pair<uint64_t, int> pUi;

int Mod(int x, int mod) { return x >= mod ? x - mod : x; }

template <int64_t mod>
class HashList {
   private:
    pUi rec[mod];
    int hd[mod], nxt[mod];

   public:
    HashList(void) {
        for (int i = 0; i < mod; i++) rec[i].first = nxt[i] = hd[i] = -1;
    }
    int update(uint64_t v, int delt) {
        int p = hd[v % mod], l = -1;
        while (~p && rec[p].first != v) l = p, p = nxt[p];
        if (rec[p].first == v) {
            if (!(rec[p].second += delt)) {
                ((~l) ? nxt[l] : hd[v % mod]) = nxt[p];
                rec[p].first = nxt[p] = -1;
                return 0;
            }
            return rec[p].second;
        }
        p = Mod((~l) ? l + 1 : v % mod, mod);
        while (~rec[p].first) p = Mod(p + 1, mod);
        ((~l) ? nxt[l] : hd[v % mod]) = p;
        return rec[p].first = v, rec[p].second = delt;
    }
};

HashList<5000000> HL;
vector<int> pos[maxn][maxk];
array<int, maxk> fa[maxn];
uint64_t val[maxn], pw[maxk];

uint64_t getVal(array<int, maxk>& a) {
    uint64_t ans = 0;
    for (int i = 0; i < maxk; i++) ans += a[i] * pw[i];
    return ans;
}

void solve(void) {
    int d, n, m;
    cin >> d >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= d; j++) fa[i][j] = i, pos[i][j].push_back(i);
    for (int i = 1; i <= n; i++) HL.update(val[i] = getVal(fa[i]), +1);
    int ans = n;
    while (m--) {
        int x, y, k;
        cin >> x >> y >> k;
        x = fa[x][k], y = fa[y][k];
        if (x != y) {
            if (pos[x][k].size() > pos[y][k].size()) swap(x, y);
            for (auto i : pos[x][k])
                pos[y][k].push_back(i), ans -= HL.update(val[i], -1) * 2,
                    ans += (HL.update(val[i] += (y - fa[i][k]) * pw[k], +1) - 1) * 2, fa[i][k] = y;
            pos[x][k].clear();
        }
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

    pw[0] = 1;
    for (int i = 1; i < maxk; i++) pw[i] = pw[i - 1] * 10009;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}