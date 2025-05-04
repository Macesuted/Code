/**
 * @file arc197_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 3000005

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int query(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += tree[i];
        return ans;
    }
    int find(int v) {
        int p = 0;
        for (int i = 22; ~i; i--)
            if (p + (1 << i) < maxn && v > (1 << i) - tree[p + (1 << i)]) v -= (1 << i) - tree[p + (1 << i)], p += 1 << i;
        return p + 1;
    }
} FT;

bool vis[maxn];

void solve(void) {
    int q;
    cin >> q;
    while (q--) {
        int A, B;
        cin >> A >> B;
        if (A < maxn && !vis[A])
            for (int i = A; i < maxn; i += A)
                if (!vis[i]) vis[i] = true, FT.add(i, +1);
        cout << FT.find(B) << endl;
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