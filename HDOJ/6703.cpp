/**
 * @file 6703.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define maxn 100005
#define maxsqrtn 260

bool mem1;

int a[maxn], bel[maxn], pos[maxn], bl[maxsqrtn], br[maxsqrtn], answer[maxsqrtn][maxn], tree[maxsqrtn][maxn];
bool vis[maxn];
int n, m;

void update(int t, int p, int v) {
    for (int i = p; i <= n; i += i & -i) tree[t][i] = min(tree[t][i], v);
    return;
}
int query(int t, int p) {
    int ans = INT_MAX;
    for (int i = p; i; i -= i & -i) ans = min(ans, tree[t][i]);
    return ans;
}

bool mem2;

void solve(void) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i;
    int B = min(n, 1500), Bcnt = n / B;
    for (int i = 1; i <= Bcnt; i++) bl[i] = br[i - 1] + 1, br[i] = br[i - 1] + B;
    if (br[Bcnt] < n) bl[Bcnt + 1] = br[Bcnt] + 1, br[Bcnt + 1] = n, Bcnt++;
    for (int i = 1; i <= Bcnt; i++) {
        for (int j = 1; j <= n; j++) tree[i][j] = INT_MAX;
        for (int j = bl[i]; j <= br[i]; j++) bel[j] = i;
        for (int j = bl[i]; j <= n; j++) vis[j] = false;
        for (int j = 1, p = bl[i]; j <= n; j++) {
            vis[a[j]] = true;
            while (vis[p]) p++;
            answer[i][j] = p;
        }
    }
    for (int i = 1, lastans = 0, op; i <= m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            int t1;
            scanf("%d", &t1);
            t1 ^= lastans;
            pos[a[t1]] = n + 1;
            for (int i = 1; i <= bel[a[t1]]; i++) update(i, t1, a[t1]);
        } else {
            int t2, t3, ans = n + 1;
            scanf("%d%d", &t2, &t3);
            t2 ^= lastans, t3 ^= lastans;
            for (int i = t3; i <= br[bel[t3]]; i++)
                if (pos[i] > t2) {
                    ans = i;
                    break;
                }
            if (ans == n + 1 && bel[t3] < Bcnt) ans = min(answer[bel[t3] + 1][t2], query(bel[t3] + 1, t2));
            printf("%d\n", lastans = ans);
        }
    }
    return;
}

int main() {
    // freopen("B.in", "r", stdin), freopen("B.out", "w", stdout);
    int _;
    scanf("%d", &_);
    while (_--) solve();
    // cerr << clock() << endl;
    return 0;
}