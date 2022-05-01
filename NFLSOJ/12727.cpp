/**
 * @file 12727.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define mod 1000000007

typedef pair<int, int> pii;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t x) { return Pow(x, mod - 2); }

vector<vector<int>> graph;
int dist[maxn * 2], f1[maxn], f2[maxn], f3[maxn];
int64_t fac[maxn], ifac[maxn], inv[maxn];
priority_queue<pii, vector<pii>, greater<pii>> p1, p2, p3;

void solve(void) {
    int K, mn = 0;
    cin >> K;
    for (int i = 1; i <= K; i++) {
        int n, m;
        cin >> n >> m;
        mn = max(mn, n);
        graph.resize(2 * n + 1);
        for (int j = 0; j < m; j++) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y + n), graph[y + n].push_back(x);
            graph[x + n].push_back(y), graph[y].push_back(x + n);
        }
        static queue<int> que;
        while (!que.empty()) que.pop();
        for (int i = 1; i <= n * 2; i++) dist[i] = 1e8;
        que.push(1), dist[1] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (dist[i] > dist[p] + 1) que.push(i), dist[i] = dist[p] + 1;
        }
        for (int j = 1; j <= n; j++)
            p1.emplace(dist[j], i), p2.emplace(dist[j + n], i), p3.emplace(max(dist[j], dist[j + n]), i);
        graph.clear();
    }
    int64_t ans = 0, a1 = 1, a2 = 1, a3 = 1;
    int cnt1 = K, cnt2 = K, cnt3 = K;
    mn *= 2;
    for (int i = 1; i <= mn; i++) {
        while (!p1.empty() && p1.top().first < i) {
            int x = p1.top().second;
            cnt1 -= !f1[x], a1 = a1 * inv[f1[x]] % mod * (f1[x] + 1) % mod, f1[x]++, p1.pop();
        }
        while (!p2.empty() && p2.top().first < i) {
            int x = p2.top().second;
            cnt2 -= !f2[x], a2 = a2 * inv[f2[x]] % mod * (f2[x] + 1) % mod, f2[x]++, p2.pop();
        }
        while (!p3.empty() && p3.top().first < i) {
            int x = p3.top().second;
            cnt3 -= !f3[x], a3 = a3 * inv[f3[x]] % mod * (f3[x] + 1) % mod, f3[x]++, p3.pop();
        }
        ans = (ans + (cnt1 ? 0 : mod - a1) + (cnt2 ? 0 : mod - a2) + (cnt3 ? 0 : a3)) % mod;
    }
    cout << (ans + mn * ((cnt1 ? 0 : a1) + (cnt2 ? 0 : a2) + (cnt3 ? 0 : mod - a3))) % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("sumdis.in", "r", stdin), freopen("sumdis.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxn; i++) inv[i] = ifac[i] * fac[i - 1] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
