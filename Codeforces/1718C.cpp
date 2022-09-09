/**
 * @file 1718C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

vector<int> prime, b;
vector<int64_t> rec[maxn];
multiset<int64_t> S[maxn];
bool np[maxn];
int a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    b.clear();
    for (auto i = prime.begin(); i != prime.end() && *i <= n; i++)
        if (n % *i == 0) b.push_back(n / *i);
    int m = b.size();
    for (int i = 0; i < m; i++) rec[i].clear(), rec[i].resize(b[i]);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) rec[i][j % b[i]] += a[j];
        S[i].clear();
        for (auto j : rec[i]) S[i].insert(j);
    }
    auto query = [&](void) {
        int64_t ans = 0;
        for (int i = 0; i < m; i++) ans = max(ans, *S[i].rbegin() * b[i]);
        return ans;
    };
    cout << query() << endl;
    while (q--) {
        int p, x;
        cin >> p >> x, p--;
        for (int i = 0; i < m; i++) S[i].erase(S[i].find(rec[i][p % b[i]])), S[i].insert(rec[i][p % b[i]] += x - a[p]);
        a[p] = x;
        cout << query() << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) {
        if (!np[i]) prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            np[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}