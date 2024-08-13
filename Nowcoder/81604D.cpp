/**
 * @file 81604D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int N = (1 << 22) + 10;
const int mod = 1e9 + 7;

class SegmentTree {
   private:
    int tree[N << 1][2];
    vector<int> node[25];

    void pushUp(int p) {
        tree[p][0] = tree[p << 1][0] + tree[p << 1 | 1][0];
        tree[p][1] = tree[p << 1][1] + tree[p << 1 | 1][1];
        return;
    }
    void build(int p, int l, int r, int d, int a[]) {
        node[d].push_back(p);
        if (l == r) return tree[p][a[l]] = 1, tree[p][!a[l]] = 0, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, d - 1, a), build(p << 1 | 1, mid + 1, r, d - 1, a);
        return pushUp(p);
    }

   public:
    void build(int d, int a[]) {
        for (int i = 0; i <= d; i++) node[i].clear();
        return build(1, 0, (1 << d) - 1, d, a);
    }
    void reverse(int d) {
        for (int i = 1; i < (int)node[d].size(); i += 2) swap(tree[node[d][i]][0], tree[node[d][i]][1]);
        for (int i = node[d][0] - 1; i; i--) pushUp(i);
        return;
    }
    int query(void) { return tree[1][1]; }
} ST;

int n, ans;
int f[N];

int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }

int64_t anss = 0;
void dfs(int d) {
    if (d == n) return ans = min(ans, ST.query()), anss = (anss + (int64_t)ST.query() * ST.query()) % mod, void();
    dfs(d + 1);
    ST.reverse(d);
    dfs(d + 1);
    ST.reverse(d);
    return;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); ++i) {
        scanf("%d", &f[i]);
    }
    int ans1 = 0;
    ans1 = add(ans1, 1ll * (1 << (n - 1)) * (1 << n) % mod * add(1 << n, mod - 1) % mod);
    ans1 = add(ans1, 1ll * (1 << n) * (1 << n) % mod);
    printf("%d ", ans1);

    ST.build(n, f);
    ans = (1 << n), dfs(0);
    for (int i = 0; i < (1 << n); i++) f[i] = !f[i];
    ST.build(n, f);
    dfs(0);
    printf("%d\n", ans);

    return 0;
}