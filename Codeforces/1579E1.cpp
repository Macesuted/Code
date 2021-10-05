/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

typedef pair<int, int> pii;

int a[maxn], p[maxn];

deque<int> front, back;

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;
    front.clear(), back.clear();
    int tail = n;
    for (register int i = 1; i <= n; i++) {
        int t = p[i];
        if (t > tail) continue;
        for (register int j = tail; j > t; j--) back.push_front(a[j]);
        front.push_back(i);
        tail = t - 1;
    }
    for (auto i : front) cout << i << ' ';
    for (auto i : back) cout << i << ' ';
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