/**
 * @file S22052.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-03
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

#define maxn 100005

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int sum;
        Node(void) { l = r = nullptr, sum = 0; }
    };

    Node *root;

    void check(Node *&p) {
        if (!p) p = new Node();
        return;
    }
    void pushUp(Node *p) { return p->sum = p->l->sum + p->r->sum, void(); }
    void insert(Node *&p, int l, int r, int qp) {
        if (l == r) return p->sum++, void();
        check(p->l), check(p->r);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    int query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return 0;
        if (ql <= l && r <= qr) return p->sum;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { root = new Node(); }
    void insert(int p) { return insert(root, 1, 2 * maxn, p); }
    int query(int l, int r = 2 * maxn) { return query(root, 1, 2 * maxn, l, r); }
} T1[2], T2[maxn];

set<int> R, C;
array<int, 4> opt[maxn];
int col[2][maxn], lcol[2][maxn], ltim[2][maxn], tim[2][maxn], ccnt[2][maxn];

queue<array<int, 3>> que;

void solve(void) {
    int n, m, k, tp;
    cin >> n >> m >> k >> tp;
    for (int i = 1; i <= n; i++) R.insert(i);
    for (int i = 1; i <= m; i++) C.insert(i);
    for (int i = 1; i <= k; i++)
        for (int j = 0; j < 4; j++) cin >> opt[i][j];
    memset(col, 0xff, sizeof(col)), memset(lcol, 0xff, sizeof(lcol));
    for (int i = k; i; i--)
        if (opt[i][0] == 0)
            for (auto j = R.lower_bound(opt[i][1]); j != R.end() && *j <= opt[i][2]; j = R.erase(j))
                que.push(array<int, 3>{0, *j, lcol[0][*j] = opt[i][3]}), ltim[0][*j] = que.size();
        else
            for (auto j = C.lower_bound(opt[i][1]); j != C.end() && *j <= opt[i][2]; j = C.erase(j))
                que.push(array<int, 3>{1, *j, lcol[1][*j] = opt[i][3]}), ltim[1][*j] = que.size();
    for (auto i : R) que.push(array<int, 3>{0, i, lcol[0][i] = 0}), ltim[0][i] = que.size();
    for (auto i : C) que.push(array<int, 3>{1, i, lcol[1][i] = 0}), ltim[1][i] = que.size();
    int cnt[2] = {n, m}, bcnt[2] = {n - 1, m - 1}, nm[2] = {n, m}, tcnt = 0;
    int64_t ans = 0;
    while (!que.empty()) {
        int w = que.front()[0], i = que.front()[1], c = que.front()[2];
        que.pop();
        col[w][i] = c, tim[w][i] = ++tcnt, cnt[w]--;
        ans += bcnt[!w] + ccnt[!w][c];
        if (col[w][i - 1] == col[w][i]) ans += cnt[!w];
        if (col[w][i + 1] == col[w][i]) ans += cnt[!w];
        if (i > 1 && !~col[w][i - 1]) bcnt[w]--, ccnt[w][c]++;
        if (i < nm[w] && !~col[w][i + 1]) bcnt[w]--, ccnt[w][c]++;
        if (~col[w][i - 1]) ccnt[w][col[w][i - 1]]--;
        if (~col[w][i + 1]) ccnt[w][col[w][i + 1]]--;
        if (!tp) continue;
        if (col[w][i - 1] == col[w][i]) T1[w].insert(tim[w][i]), T1[w].insert(tim[w][i - 1]);
        if (col[w][i + 1] == col[w][i]) T1[w].insert(tim[w][i]), T1[w].insert(tim[w][i + 1]);
        if (i > 1) ans += T1[!w].query(1, tim[w][i - 1]);
        if (i < nm[w]) ans += T1[!w].query(1, tim[w][i + 1]);
        if (w) {
            if (i > 1) T2[col[w][i]].insert(ltim[w][i - 1]);
            if (i < nm[w]) T2[col[w][i]].insert(ltim[w][i + 1]);
        } else {
            if (i > 1) ans += T2[lcol[w][i - 1]].query(ltim[w][i - 1]);
            if (i < nm[w]) ans += T2[lcol[w][i + 1]].query(ltim[w][i + 1]);
        }
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("painting.in", "r", stdin), freopen("painting.out", "w", stdout);
#endif
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