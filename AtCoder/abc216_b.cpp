/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 500005
#define mod 998244353

typedef pair<int, int> pii;

map<string, set<string> > record;

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) {
        string a, b;
        cin >> a >> b;
        if (record[a].count(b)) return cout << "Yes" << endl, void();
        record[a].insert(b);
    }
    cout << "No" << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    cout << setiosflags(ios::fixed) << setprecision(11);
    while (_--) work();
    return 0;
}