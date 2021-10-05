/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

priority_queue<pii, vector<pii>, less<pii> > que;

int a[maxn];
vector<pii> answer;

void work(void) {
    int n;
    cin >> n;
    while (!que.empty()) que.pop();
    answer.clear();
    for (register int i = 1, t; i <= n; i++) cin >> t, que.push({t, i});
    while (true) {
        pii p1 = que.top();
        que.pop();
        pii p2 = que.top();
        que.pop();
        if (p2.first == 0) break;
        answer.emplace_back(p1.second, p2.second);
        p1.first--, p2.first--;
        que.push(p1), que.push(p2);
    }
    cout << answer.size() << endl;
    for (auto i : answer) cout << i.first << ' ' << i.second << endl;
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