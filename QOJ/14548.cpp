/**
 * @file 14548.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

struct Block {
    int64_t val, cnt;
    int top;

    bool operator<(const Block& o) const {
        if (this->val * o.cnt != o.val * this->cnt) return this->val * o.cnt < o.val * this->cnt;
        return this->top < o.top;
    }
};

vector<int> graph[maxn];
Block a[maxn];
int fa[maxn], f[maxn];

int getfa(int p) { return f[p] == p ? p : f[p] = getfa(f[p]); }

void dfs(int p, int pre = 0) {
    fa[p] = pre;
    for (auto q : graph[p])
        if (q != pre) dfs(q, p);
    return;
}

void solve(void) {
    int n, X;
    cin >> n >> X;

    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    int64_t ans = 0;

    for (int i = 2, op; i <= n; i++) {
        cin >> op;
        if (op == 1)
            a[i] = {0, 1, i};
        else {
            int64_t x, d, h;
            cin >> x >> d >> h;
            a[i] = {h / (X - d) + (h % (X - d) > 0) - 1, 0, i};
            ans -= a[i].val * x;
        }
    }

    dfs(1);

    for (int i = 1; i <= n; i++) f[i] = i;

    multiset<Block> S;

    a[1] = {0, 0, 1};
    for (int i = 2; i <= n; i++)
        if (a[i].val > 0 || a[i].cnt > 0) S.insert(a[i]);

    while (!S.empty()) {
        int p = S.begin()->top, q = getfa(fa[p]);
        S.erase(a[p]);
        if (q != 1) S.erase(a[q]);

        ans += a[q].cnt * a[p].val;
        a[q].val += a[p].val;
        a[q].cnt += a[p].cnt;
        f[p] = q;

        if (q != 1) S.insert(a[q]);
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}