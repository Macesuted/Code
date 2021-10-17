/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 400005

int a[maxn];
int n, k;

void work(void) {
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> a[i];
    sort(a + 1, a + k + 1);
    int rest = n - 1, answer = 0;
    for (int i = k; i; i--) {
        rest -= n - a[i];
        if (rest < 0) break;
        answer++;
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}