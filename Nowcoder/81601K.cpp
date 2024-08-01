/**
 * @file 81601K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 5005

class Queue {
   private:
    int a[maxn], pl, pr;

    void pushFront(int v) { return a[++pr] = v, void(); }
    void popFront() { return pr--, void(); }
    void popBack() { return pl++, void(); }

   public:
    int front(void) { return a[pr]; }
    int back(void) { return a[pl]; }

    int size(void) { return pr - pl + 1; }
    bool empty(void) { return size() == 0; }

    void clear(void) { return pl = 1, pr = 0, void(); }
    void push(int v) {
        while (!empty() && front() > v) popFront();
        return pushFront(v);
    }
    void pop(int v) {
        if (!empty() && back() == v) popBack();
        return;
    }
} que;

int a[maxn], f[maxn][maxn], vl[maxn], vr[maxn];

void update(int l, int r, int v) {
    for (int i = 0; i < l; i++) f[i + 1][r] = min(f[i + 1][r], f[i][l - 1] + v);
    return;
}

void solve(int l, int r) {
    if (l == r) return update(l, l, 0);

    int mid = (l + r) >> 1;
    solve(l, mid);

    vl[mid] = vr[mid] = a[mid], vl[mid + 1] = vr[mid + 1] = a[mid + 1];
    for (int i = mid - 1; i >= l; i--) vl[i] = min(vl[i + 1], a[i]), vr[i] = max(vr[i + 1], a[i]);
    for (int i = mid + 2; i <= r; i++) vl[i] = min(vl[i - 1], a[i]), vr[i] = max(vr[i - 1], a[i]);

    for (int k = 0; k <= mid; k++) {
        que.clear();
        for (int p = mid + 1, pl = mid, pr = mid; p <= r; p++) {
            while (pl >= l) que.push(f[k][pl - 1] + vr[pl] - vl[pl]), pl--;
            while (pr > pl && !(vl[pr] <= vl[p] && vr[p] <= vr[pr])) que.pop(f[k][pr - 1] + vr[pr] - vl[pr]), pr--;
            if (!que.empty()) f[k + 1][p] = min(f[k + 1][p], que.back());
        }
        que.clear();
        for (int p = mid + 1, pl = mid; p <= r; p++) {
            while (pl >= l && (vl[p] <= vl[pl] && vr[pl] <= vr[p])) que.push(f[k][pl - 1]), pl--;
            if (!que.empty()) f[k + 1][p] = min(f[k + 1][p], que.back() + vr[p] - vl[p]);
        }
        que.clear();
        for (int p = mid + 1, pl = mid, pr = mid; p <= r; p++) {
            while (pl >= l && vl[p] <= vl[pl]) que.push(f[k][pl - 1] + vr[pl]), pl--;
            while (pr > pl && !(vr[p] <= vr[pr])) que.pop(f[k][pr - 1] + vr[pr]), pr--;
            if (!que.empty()) f[k + 1][p] = min(f[k + 1][p], que.back() - vl[p]);
        }
        que.clear();
        for (int p = mid + 1, pl = mid, pr = mid; p <= r; p++) {
            while (pl >= l && vr[pl] <= vr[p]) que.push(f[k][pl - 1] - vl[pl]), pl--;
            while (pr > pl && !(vl[pr] <= vl[p])) que.pop(f[k][pr - 1] - vl[pr]), pr--;
            if (!que.empty()) f[k + 1][p] = min(f[k + 1][p], que.back() + vr[p]);
        }
    }

    solve(mid + 1, r);

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) f[i][j] = 1e9;
    f[0][0] = 0;
    solve(1, n);
    for (int i = 1; i <= n; i++) cout << f[i][n] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}