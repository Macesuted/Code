/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

set<int> graph[maxn];

inline bool check(int x) { return graph[x].empty() || *--graph[x].end() < x; }

void work(void) {
    int n, m;
    cin >> n >> m;
    for (register int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].insert(y), graph[y].insert(x);
    }
    int answer = 0;
    for (register int i = 1; i <= n; i++)
        if (check(i)) answer++;
    int q;
    cin >> q;
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            if (check(x)) answer--;
            if (check(y)) answer--;
            graph[x].insert(y), graph[y].insert(x);
            if (check(x)) answer++;
            if (check(y)) answer++;
        } else if (opt == 2) {
            int x, y;
            cin >> x >> y;
            if (check(x)) answer--;
            if (check(y)) answer--;
            graph[x].erase(y), graph[y].erase(x);
            if (check(x)) answer++;
            if (check(y)) answer++;
        } else
            cout << answer << endl;
    }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}