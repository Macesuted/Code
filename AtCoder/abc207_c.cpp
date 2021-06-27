/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 2005
typedef pair<int, int> pii;

pii a[maxn];
int cac[maxn << 1];
int tree[maxn << 1];

void add(int p, int val) {
    for (register int i = p; i < (maxn << 1); i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l *= 2, r *= 2;
        if (t == 3 || t == 4) l++;
        if (t == 2 || t == 4) r--;
        a[i] = (pii){l, r};
        cac[i] = l, cac[i + n] = r;
    }
    sort(cac + 1, cac + 2 * n + 1);
    int tn = unique(cac + 1, cac + 2 * n + 1) - cac - 1;
    for (register int i = 1; i <= n; i++) a[i].first = lower_bound(cac + 1, cac + tn + 1, a[i].first) - cac,
                                          a[i].second = lower_bound(cac + 1, cac + tn + 1, a[i].second) - cac;
    sort(a + 1, a + n + 1);
    int answer = 0;
    for (register int i = 1; i <= n; i++) {
        answer += (i - 1) - sum(a[i].first - 1);
        add(a[i].second, 1);
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}