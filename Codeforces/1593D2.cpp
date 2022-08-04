/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1005

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

map<int, int> S;
set<int> T;

void work(void) {
    S.clear();
    int n, answer = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        S[x]++;
    }
    for (auto i = S.begin(); i != S.end(); i++) {
        if (i->second * 2 >= n) return cout << -1 << endl, void();
        T.clear();
        for (auto j : S) {
            if (j.first <= i->first) continue;
            int p = j.first - i->first;
            for (int k = 1; k * k <= p; k++)
                if (p % k == 0) T.insert(k), T.insert(p / k);
        }
        for (auto g : T) {
            int cnt = 0;
            for (auto k : S)
                if (k.first >= i->first && (k.first - i->first) % g == 0) cnt += k.second;
            if (cnt * 2 >= n) answer = max(answer, g);
        }
    }
    cout << (answer == 0 ? -1 : answer) << endl;
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