/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005

void work(void) {
    int a, b, c, maxx;
    cin >> a >> b >> c;
    maxx = max({a, b, c});
    cout << max({0LL, b - a + 1, c - a + 1}) << ' ';
    cout << max({0LL, a - b + 1, c - b + 1}) << ' ';
    cout << max({0LL, a - c + 1, b - c + 1}) << endl;
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