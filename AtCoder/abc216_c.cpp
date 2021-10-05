/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 500005
#define mod 998244353

typedef pair<int, int> pii;

stack<int> vec;

void work(void) {
    int n;
    cin >> n;
    while (n) vec.push(n & 1), n >>= 1;
    while (!vec.empty()) {
        cout << "B";
        if (vec.top()) cout << "A";
        vec.pop();
    }
    cout << endl;
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