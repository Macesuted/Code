/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 600005

class SegmentTree {
   private:
    int tree[maxn << 2], lazy[maxn << 2];

    inline void pushDown(int p) {
        if (!lazy[p]) return;
        tree[p << 1] += lazy[p], tree[p << 1 | 1] += lazy[p];
        lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) return tree[p] += val, lazy[p] += val, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
        return;
    }
    int get(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1, answer = 0;
        if (ql <= mid) answer = max(answer, get(p << 1, l, mid, ql, qr));
        if (qr > mid) answer = max(answer, get(p << 1 | 1, mid + 1, r, ql, qr));
        return answer;
    }

   public:
    int n;

    inline void build(int tn) {
        n = tn;
        for (register int i = 1; i <= (n << 2); i++) tree[i] = lazy[i] = 0;
        return;
    }
    inline void update(int l, int r, int val) { return update(1, 1, n, l, r, val); }
    inline int get(int l, int r) { return get(1, 1, n, l, r); }
} sgtree;

vector<vector<int> > tree[2];
int dfni[maxn], dfno[maxn];

int tim, answer, cnt;
void dfs(int p) {
    dfni[p] = ++tim;
    for (vector<int>::iterator i = tree[1][p].begin(); i != tree[1][p].end(); i++) dfs(*i);
    dfno[p] = tim;
    return;
}
void dfs2(int p) {
    int val = sgtree.get(dfni[p], dfni[p]), rec = 0;
    if (val) {
        sgtree.update(dfni[val], dfno[val], -val);
        rec = val;
        sgtree.update(dfni[p], dfno[p], p);
    } else if (sgtree.get(dfni[p], dfno[p]))
        rec = p;
    else
        sgtree.update(dfni[p], dfno[p], p), cnt++;
    answer = max(answer, cnt);
    for (vector<int>::iterator i = tree[0][p].begin(); i != tree[0][p].end(); i++) dfs2(*i);
    if (rec)
        sgtree.update(dfni[rec], dfno[rec], rec);
    else
        cnt--;
    sgtree.update(dfni[p], dfno[p], -p);
    return;
}

void work(void) {
    int n;
    cin >> n;
    tree[0].resize(n + 1), tree[1].resize(n + 1);
    for (register int i = 2, x; i <= n; i++) cin >> x, tree[0][x].push_back(i);
    for (register int i = 2, x; i <= n; i++) cin >> x, tree[1][x].push_back(i);
    tim = 0, dfs(1);
    answer = cnt = 0;
    sgtree.build(n);
    dfs2(1);
    cout << answer << endl;
    tree[0].clear(), tree[1].clear();
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) work();
    return 0;
}