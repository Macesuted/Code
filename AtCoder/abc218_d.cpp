/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 2005

typedef pair<int, int> pii;

map<int, set<int>> S;

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        S[x].insert(y);
    }
    int answer = 0;
    for (auto i = S.begin(); i != S.end(); i++) {
        auto j = i;
        j++;
        for (; j != S.end(); j++) {
            int cnt = 0;
            auto x = i->second.begin(), y = j->second.begin();
            while (x != i->second.end() && y != j->second.end()) {
                if (*x == *y) cnt++;
                (*x < *y) ? x++ : y++;
            }
            answer += cnt * (cnt - 1) / 2;
        }
    }
    cout << answer << endl;
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