/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Opt {
    int l, r, d;
};

vector<int> a, b;
vector<Opt> answer;

void work(void) {
    int n;
    cin >> n;
    a.resize(n + 1), b.resize(n + 1);
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i < n; i++) {
        int maxp = i;
        for (register int j = i + 1; j <= n; j++)
            if (a[j] < a[maxp]) maxp = j;
        if (maxp == i) continue;
        int d = maxp - i;
        answer.push_back((Opt){i, maxp, d});
        while (d--) {
            int p = a[i];
            for (register int j = i; j < maxp; j++) a[j] = a[j + 1];
            a[maxp] = p;
        }
    }
    cout << answer.size() << endl;
    for (auto i : answer) cout << i.l << ' ' << i.r << ' ' << i.d << endl;
    a.clear(), answer.clear();
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