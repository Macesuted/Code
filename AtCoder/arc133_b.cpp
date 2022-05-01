/**
 * @file arc133_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] = max(tree[i], v);
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum = max(sum, tree[i]);
        return sum;
    }
};

int a[maxn], b[maxn], p[maxn], q[maxn];
FenwickTree FT;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;
    for (int i = 1; i <= n; i++) cin >> b[i], q[b[i]] = i;
    for (int i = 1; i <= n; i++) {
        vector<int> pos;
        for (int vj = a[i]; vj <= n; vj += a[i]) pos.push_back(q[vj]);
        sort(pos.begin(), pos.end(), greater<int>());
        for (auto j : pos) FT.add(j, FT.sum(j - 1) + 1);
    }
    cout << FT.sum(n) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
