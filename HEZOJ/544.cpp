/**
 * @file 544.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-16
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

#define maxn 100005

bool done[maxn];

class SegmentTree {
   private:
    int n;
    vector<int> pos[maxn << 2];

    vector<int> merge(vector<int> a, vector<int> b) {
        for (auto i : b) a.push_back(i);
        return a;
    }
    void insert(int p, int l, int r, int ql, int qr, int id) {
        if (ql <= l && r <= qr) return pos[p].push_back(id);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, id);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, id);
        return;
    }
    vector<int> query(int p, int l, int r, int qp) {
        vector<int> tmp;
        for (auto i : pos[p])
            if (!done[i]) tmp.push_back(i);
        pos[p] = tmp;
        if (l == r) return pos[p];
        int mid = (l + r) >> 1;
        return merge(qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp), pos[p]);
    }
    void clear(int p, int l, int r) {
        pos[p].clear();
        if (l == r) return;
        int mid = (l + r) >> 1;
        clear(p << 1, l, mid), clear(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, int id) { return insert(1, 1, n, l, r, id); }
    vector<int> query(int p) { return query(1, 1, n, p); }
    void clear(void) { return clear(1, 1, n); }
} ST;

int a[maxn], sum[maxn], l[maxn], r[maxn], rest[maxn];

void solve(void) {
    int n, B, cnt;
    cin >> n, B = cnt = sqrt(n), ST.resize(n);
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i] >> a[i], done[i] = false;
    while (cnt >= B) {
        vector<int> S;
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + done[i];
        queue<int> que;
        for (int i = 1; i <= n; i++) {
            if (done[i]) continue;
            int v = a[i] - sum[r[i]] + sum[l[i] - 1];
            if (v <= 0)
                que.push(i), done[i] = true;
            else if (v <= B)
                S.push_back(i), ST.insert(l[i], r[i], i), rest[i] = v;
        }
        cnt = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop(), cnt++;
            vector<int> ret = ST.query(p);
            for (auto i : ret)
                if (--rest[i] == 0) que.push(i), done[i] = true;
        }
        ST.clear();
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += done[i];
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}