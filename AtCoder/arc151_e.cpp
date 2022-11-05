/**
 * @file arc151_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-04
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
#define base 19260817

typedef pair<int, int> pii;

template <int64_t mod>
class Hash {
   private:
    int64_t h[maxn], pw[maxn];

   public:
    void init(int n, int a[]) {
        h[0] = 0, pw[0] = 1;
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * base + a[i]) % mod, pw[i] = pw[i - 1] * base % mod;
        return;
    }
    int64_t getHash(int l, int r) { return (h[r] + mod - h[l - 1] * pw[r - l + 1] % mod) % mod; }
};
Hash<1000000007> hb1, hc1;
Hash<1000000009> hb2, hc2;

int n, p, q, a[maxn], b[maxn], c[maxn], dist[maxn];
set<pair<int64_t, int64_t>> S;
vector<int> graph[maxn];
queue<int> que;

bool check(int len) {
    S.clear();
    for (int i = 1; i + len - 1 <= p; i++) S.emplace(hb1.getHash(i, i + len - 1), hb2.getHash(i, i + len - 1));
    for (int i = 1; i + len - 1 <= q; i++)
        if (S.count({hc1.getHash(i, i + len - 1), hc2.getHash(i, i + len - 1)})) return true;
    return false;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> p;
    for (int i = 1; i <= p; i++) cin >> b[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> c[i];
    hb1.init(p, b), hb2.init(p, b), hc1.init(q, c), hc2.init(q, c);
    int l = 0, r = min(p, q) + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) ? l : r) = mid;
    }
    if (l) return cout << p + q - 2 * l << endl, void();
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i < n; i++) graph[a[i]].push_back(a[i + 1]), graph[a[i + 1]].push_back(a[i]);
    for (int i = 1; i <= p; i++) dist[b[i]] = 0, que.push(b[i]);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (dist[i] > dist[p] + 1) dist[i] = dist[p] + 1, que.push(i);
    }
    int ans = INT_MAX;
    for (int i = 1; i <= q; i++) ans = min(ans, dist[c[i]]);
    cout << 2 * ans + p + q - 2 << endl;
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