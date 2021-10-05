/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 100005

int a[maxn], b[maxn], suma[maxn], sumb[maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= n; i++) cin >> b[i];
    int ansa = 0, ansb = 0, cnt = n - (n / 4);
    sort(a + 1, a + n + 1, greater<int>()), sort(b + 1, b + n + 1, greater<int>());
    for (register int i = 1; i <= n; i++) suma[i] = suma[i - 1] + a[i];
    for (register int i = 1; i <= n; i++) sumb[i] = sumb[i - 1] + b[i];
    for (register int i = 0;; i++) {
        int cnt = (n + i) - ((n + i) / 4);
        int ansa = 0;
        if (i > cnt)
            ansa = cnt * 100;
        else
            ansa = i * 100 + suma[cnt - i];
        int ansb = sumb[min(n, cnt)];
        if (ansa >= ansb) {
            cout << i << endl;
            return;
        }
    }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}