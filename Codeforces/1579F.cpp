/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005

typedef pair<int, int> pii;

vector<vector<bool>> S;

int a[maxn];
bool vis[maxn];

void work(void) {
    S.clear();
    int n, d;
    cin >> n >> d;
    for (register int i = 0; i < n; i++) cin >> a[i], vis[i] = false;
    for (register int i = 0; i < n; i++) {
        if (vis[i]) continue;
        int p = i;
        S.push_back({});
        while (!vis[p]) {
            vis[p] = true;
            S.back().push_back(a[p]);
            p = (p + d) % n;
        }
    }
    int answer = 0;
    for (auto i : S) {
        bool check = true, pre = true;
        int preLen = 0, len = 0;
        for (auto j : i)
            if (!j)
                check = pre = false, answer = max(answer, len), len = 0;
            else {
                if (pre) preLen++;
                len++;
            }
        answer = max(answer, preLen + len);
        if (check) return cout << -1 << endl, void();
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