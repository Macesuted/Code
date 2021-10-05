/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

vector<int> a[maxn];
set<int> top[maxn];

queue<int> que;
int rest;

void clearQue(void) {
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (top[p].size() <= 1) continue;
        int x = *top[p].begin();
        top[p].erase(top[p].begin());
        int y = *top[p].begin();
        top[p].erase(top[p].begin());
        rest -= 2;
        a[x].pop_back(), a[y].pop_back();
        if (a[x].size()) {
            top[a[x].back()].insert(x);
            if (top[a[x].back()].size() > 1) que.push(a[x].back());
        }
        if (a[y].size()) {
            top[a[y].back()].insert(y);
            if (top[a[y].back()].size() > 1) que.push(a[y].back());
        }
    }
    return;
}

void work(void) {
    int n, m;
    cin >> n >> m;
    rest = 2 * n;
    for (register int i = 1; i <= m; i++) {
        int t;
        cin >> t;
        a[i].resize(t);
        for (register int j = t - 1; ~j; j--) cin >> a[i][j];
        if (t) {
            top[a[i].back()].insert(i);
            if (top[a[i].back()].size() > 1) que.push(a[i].back()), clearQue();
        }
    }
    if (rest)
        cout << "No";
    else
        cout << "Yes";
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