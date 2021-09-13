/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 305
#define maxn2 90005

int a[maxn2];

class BIT {
   public:
    int tree[maxn2];
    void update(int p, int val) {
        for (register int i = p; i < maxn2; i += i & -i) tree[i] += val;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (register int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} tree;

map<int, vector<int> > S;

queue<int> mark, cache;

void work(void) {
    int n, m;
    cin >> n >> m;
    S.clear();
    int answer = 0;
    for (register int i = 1; i <= n * m; i++) cin >> a[i], S[a[i]].push_back(n * m - i + 1);
    for (register int i = n; i; i--) {
        for (register int j = m; j; j--) {
            auto it = --S.end();
            int p = it->second.back();
            it->second.pop_back();
            answer += tree.sum(p), cache.push(p);
            if (it->second.empty()) {
                while (!cache.empty()) {
                    int t = cache.front();
                    cache.pop();
                    tree.update(t, +1), mark.push(t);
                }
                S.erase(--S.end());
            }
        }
        while (!cache.empty()) cache.pop();
        while (!mark.empty()) tree.update(mark.front(), -1), mark.pop();
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}