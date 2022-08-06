/**
 * @file 749.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-06
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

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t sum;
        int cnt;
        Node(void) { l = r = nullptr, cnt = sum = 0; }
    };

    Node buf[15000000];
    int bufcnt;

    vector<Node*> roots;

    int getCnt(Node* p) { return p ? p->cnt : 0; }
    int64_t getSum(Node* p) { return p ? p->sum : 0; }
    Node* newNode(void) { return &(buf[bufcnt++] = Node()); }
    void insert(Node*& p, Node* o, int l, int r, int qp) {
        p = newNode();
        if (o) *p = *o;
        p->cnt++, p->sum += qp;
        if (l == r) return;
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, o ? o->l : nullptr, l, mid, qp) : insert(p->r, o ? o->r : nullptr, mid + 1, r, qp);
        return;
    }
    int64_t query(Node* v1, Node* v2, int l, int r, int cnt) {
        if (l == r) return min(cnt, getCnt(v1) + getCnt(v2)) * (int64_t)l;
        int mid = (l + r) >> 1, rcnt = (v1 ? getCnt(v1->r) : 0) + (v2 ? getCnt(v2->r) : 0);
        if (rcnt >= cnt) return query(v1 ? v1->r : nullptr, v2 ? v2->r : nullptr, mid + 1, r, cnt);
        return (v1 ? getSum(v1->r) : 0) + (v2 ? getSum(v2->r) : 0) +
               query(v1 ? v1->l : nullptr, v2 ? v2->l : nullptr, l, mid, cnt - rcnt);
    }

   public:
    SegmentTree(void) { bufcnt = 0, roots.push_back(nullptr); }
    void clear(void) { bufcnt = 0, roots.clear(), roots.push_back(nullptr); }
    void insert(int o, int v) { return roots.push_back(roots.back()), insert(roots.back(), roots[o], 1, 1e9, v); }
    int64_t query(int v1, int v2, int cnt) { return query(roots[v1], roots[v2], 1, 1e9, cnt); }
} ST;

int a[maxn], ql[maxn], qr[maxn], ver[maxn];
int64_t ans[maxn];
vector<int> S[maxn];
priority_queue<int, vector<int>, greater<int>> que;

void solve(int l, int r, vector<int> ques) {
    if (ques.empty()) return;
    if (l == r) {
        for (auto i : ques) ans[i] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    vector<int> L, R;
    for (int i = mid + 1; i <= r; i++) S[i].clear();
    for (auto i : ques)
        if (qr[i] <= mid)
            L.push_back(i);
        else if (ql[i] > mid)
            R.push_back(i);
        else
            S[qr[i]].push_back(i);
    for (int o = 0; o < 2; o++) {
        int vcnt = 0;
        ST.clear();
        for (int i = mid; i >= l; i--) {
            que.push(-a[i]), ver[i] = (i == mid ? 0 : ver[i + 1]);
            if (((mid - i) & 1) == o) ST.insert(ver[i], -que.top()), que.pop(), ver[i] = ++vcnt;
        }
        while (!que.empty()) que.pop();
        int64_t sum = 0;
        for (int i = mid + 1; i <= r; i++) {
            que.push(a[i]), sum += a[i], ver[i] = (i == mid + 1 ? 0 : ver[i - 1]);
            if (((i - mid) & 1) == !o) ST.insert(ver[i], que.top()), sum -= que.top(), que.pop(), ver[i] = ++vcnt;
            for (auto q : S[i])
                if (((mid - ql[q]) & 1) == o) ans[q] = sum + ST.query(ver[ql[q]], ver[qr[q]], (mid - ql[q] + 2) / 2);
        }
        while (!que.empty()) que.pop();
    }
    return solve(l, mid, L), solve(mid + 1, r, R);
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> ques;
    for (int i = 1; i <= q; i++) cin >> ql[i] >> qr[i], ques.push_back(i);
    solve(1, n, ques);
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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