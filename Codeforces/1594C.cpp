/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

typedef pair<int, int> pii;

void work(void) {
    int n;
    char c;
    cin >> n >> c;
    string s;
    cin >> s;
    s = ' ' + s;
    bool check1 = true, check2 = (s[n] == c);
    for (int i = 1; i < n; i++)
        if (s[i] != c) check1 = false;
    if (check1 && check2) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        int ttt = 0;
        for (int j = i; j <= n; j += i) ttt += (s[j] != c);
        if (ttt == 0) {
            cout << 1 << endl << i << endl;
            return;
        }
    }
    vector<int> ans;
    if (!check2) ans.push_back(n - 1);
    if (!check1) ans.push_back(n);
    cout << ans.size() << endl;
    if (ans.empty()) return;
    for (auto i : ans) cout << i << ' ';
    cout << endl;
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