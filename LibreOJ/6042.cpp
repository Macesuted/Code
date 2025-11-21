/**
 * @file 6042.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-03
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

#define maxn 1000005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    int sum[maxn << 2], cnt[maxn << 2], n;

    void pushUp(int p) { return sum[p] = sum[p << 1] + sum[p << 1 | 1], cnt[p] = cnt[p << 1] + cnt[p << 1 | 1], void(); }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return sum[p] += v * l, cnt[p] += v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    pii query(int p, int l, int r, int v) {
        if (l == r) {
            int c = v / l + (v % l > 0);
            return {c, c * l};
        }
        int mid = (l + r) >> 1;
        if (sum[p << 1 | 1] < v) {
            pii ret = query(p << 1, l, mid, v - sum[p << 1 | 1]);
            return {ret.first + cnt[p << 1 | 1], ret.second + sum[p << 1 | 1]};
        }
        return query(p << 1 | 1, mid + 1, r, v);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    pii query(int v) { return query(1, 1, n, v); }
};

SegmentTree ST;
vector<int> graph[maxn];
int n, siz[maxn], ans[maxn];
multiset<int> S;

pii dfs1(int p, int pre = -1) {
    pii ans = {0x3f3f3f3f, p};
    siz[p] = 1;
    int maxSon = 0;
    for (auto i : graph[p])
        if (i != pre) ans = min(ans, dfs1(i, p)), siz[p] += siz[i], maxSon = max(maxSon, siz[i]);
    return min(ans, pii{max(maxSon, n - siz[p]), p});
}
void dfs2(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre) dfs2(i, p), siz[p] += siz[i];
    return;
}

void solve(void) {
    cin >> n;
    for (int i = 1, u, v; i < n; i++) cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);
    ST.resize(n);
    int root = dfs1(1).second;
    dfs2(root);
    for (auto i : graph[root]) ST.insert(siz[i], +1);
    for (auto i : graph[root]) {
        ST.insert(siz[i], -1);
        int cnt, sum;
        tie(cnt, sum) = ST.query(n - siz[i] - n / 2);
        static queue<int> que;
        que.push(i);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            ans[p] = cnt + (n - siz[p] - sum > n / 2);
            for (auto i : graph[p])
                if (!ans[i] && i != root) que.push(i);
        }
        ST.insert(siz[i], +1);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
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