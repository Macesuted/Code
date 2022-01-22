/**
 * @file 1629C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

int a[200005], cnt[200005], cntb[200005];
set<int> S;

void solve(void) {
    int n;
    cin >> n;
    S.clear();
    for (int i = 0; i <= n; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
    for (int i = 0; i <= n; i++)
        if (!cnt[i]) S.insert(i);
    static vector<int> answer;
    answer.clear();
    for (int l = 1, r; l <= n; l = r + 1) {
        int t = *S.begin(), mex = 0;
        cntb[a[r = l]]++;
        while (cntb[mex]) mex++;
        while (mex < t) {
            cntb[a[++r]]++;
            while (cntb[mex]) mex++;
        }
        answer.push_back(mex);
        for (int i = l; i <= r; i++) {
            if (!--cnt[a[i]]) S.insert(a[i]);
            cntb[a[i]]--;
        }
    }
    cout << answer.size() << endl;
    for (auto i : answer) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
