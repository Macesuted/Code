/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

map<int, int> f;

int dfs(int n, int t, bool preZero = false) {
    int ans = 0x3f3f3f3f;
    if (f.count(n)) ans = f[n];
    if (t > n) return ans;
    ans = min(ans, dfs(n, t * 10, n / t % 10 == 0));
    n = n % t + n / (t * 10) * t;
    if (!(n < t && preZero)) ans = min(ans, dfs(n, t, preZero) + 1);
    return ans;
}

void work(void) {
    int n;
    cin >> n;
    cout << dfs(n, 1) << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    f[0] = 1;
    for (register int i = 1; i <= 1e18; i <<= 1) {
        int t = i, cnt = 0;
        while (t) {
            if (f.find(t) == f.end())
                f[t] = cnt;
            else
                f[t] = min(f[t], cnt);
            t /= 10, cnt++;
        }
    }
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}