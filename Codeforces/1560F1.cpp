/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

deque<int> a;
set<int> S;
int k, pow10[10];

int add(int l, int r) {
    int t = 1;
    while (t <= r) t *= 10;
    return l * t + r;
}

int answer;
int dfs(int p, int n, bool lim = true) {
    if (p == n) return 0;
    if (!lim) {
        if (k) return 0;
        return *S.begin() * pow10[n - p - 1] + dfs(p + 1, n, false);
    }
    int ans = 0x3f3f3f3f3f3f3f3f;
    if (S.find(a[p]) != S.end() || k) {
        bool use = false;
        if (S.find(a[p]) == S.end()) use = true, k--, S.insert(a[p]);
        ans = min(ans, a[p] * pow10[n - p - 1] + dfs(p + 1, n, true));
        if (use) k++, S.erase(a[p]);
    }
    if (S.upper_bound(a[p]) != S.end())
        ans = min(ans, *S.upper_bound(a[p]) * pow10[n - p - 1] + dfs(p + 1, n, false));
    if (a[p] < 9 && k) {
        k--, S.insert(a[p] + 1);
        ans = min(ans, (a[p] + 1) * pow10[n - p - 1] + dfs(p + 1, n, false));
        k++, S.erase(a[p] + 1);
    }
    return ans;
}

void work(void) {
    int n;
    cin >> n >> k;
    while (n) a.push_front(n % 10), n /= 10;
    int tn = a.size();
    answer = 0;
    cout << dfs(0, tn) << endl;
    a.clear();
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    pow10[0] = 1;
    for (register int i = 1; i < 10; i++) pow10[i] = pow10[i - 1] * 10;
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}