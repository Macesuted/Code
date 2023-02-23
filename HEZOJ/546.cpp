/**
 * @file 546.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-15
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
#define maxsqrtn 320

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];
    stack<pii> op;

   public:
    void update(int p, int v) {
        op.emplace(p, v);
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int query(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
    int getPos(int lim) {
        int p = 0;
        for (int i = 16, tot = 0; ~i; i--)
            if ((p | (1 << i)) + tot + tree[p | (1 << i)] < lim) tot += tree[p |= 1 << i];
        return p + 1;
    }
    void clear(void) {
        while (!op.empty()) update(op.top().first, -op.top().second), op.pop(), op.pop();
        return;
    }
} FT[maxsqrtn];

int a[maxn], bel[maxn], L[maxsqrtn], R[maxsqrtn];

void build(int s) {
    FT[s].clear();
    for (int i = L[s]; i <= R[s]; i++) FT[s].update(FT[s].getPos(a[i]), 1);
    return;
}

void solve(void) {
    int n, m = 0, B, q;
    cin >> n, B = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    while (R[m] != n) L[m + 1] = R[m] + 1, R[m + 1] = min(n, R[m] + B), m++;
    for (int i = 1; i <= m; i++)
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
    for (int i = 1; i <= m; i++) build(i);
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            cin >> a[x], build(bel[x]);
        else {
            int bx = bel[x], ans = a[x];
            for (int i = x + 1; i <= R[bx]; i++) ans += a[i] <= ans;
            for (int i = bx + 1; i <= m; i++) ans += FT[i].query(ans);
            cout << ans << endl;
        }
    }
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