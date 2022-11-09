/**
 * @file 1354G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

mt19937 rnd(114514);

int query(vector<int> a, vector<int> b) {
    cout << "? " << a.size() << ' ' << b.size() << endl;
    for (auto i : a) cout << i << ' ';
    cout << endl;
    for (auto i : b) cout << i << ' ';
    cout << endl;
    string s;
    cin >> s;
    return s == "FIRST" ? -1 : (s == "EQUAL" ? 0 : 1);
}
vector<int> genVec(int l, int r) {
    vector<int> ans;
    for (int i = l; i <= r; i++) ans.push_back(i);
    return ans;
}

void solve(void) {
    int n, k, cnt = 0;
    cin >> n >> k;
    for (int i = 1; i <= 10; i++) cnt += (query({1}, {int(rnd() % (n - 1) + 2)}) == 1);
    if (cnt) return cout << "! 1" << endl, void();
    int l = 2, r = n;
    while (l != r) {
        int len = min(l - 1, (r - l + 1) / 2), ret = query(genVec(1, len), genVec(l, l + len - 1));
        if (ret == -1)
            r = l + len - 1;
        else
            l = l + len;
    }
    cout << "! " << l << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}