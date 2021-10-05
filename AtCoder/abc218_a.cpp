/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef pair<int, int> pii;

void work(void) {
    int n;
    string s;
    cin >> n >> s;
    if (s[n - 1] == 'o')
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cout << setprecision(11);
    // cin >> _;
    while (_--) work();
    return 0;
}