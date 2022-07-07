/**
 * @file 102759L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-07
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

#define maxn 250005

typedef pair<int, int> pii;

int h[maxn], l[maxn];
map<int, int> S;
vector<int> vec1;
vector<pii> vec2;
priority_queue<int, vector<int>, greater<int>> R;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i] >> l[i];
    for (int i = 1; i < n; i++)
        if (h[i] != h[i + 1] && l[i] != l[i + 1]) vec1.push_back(i);
    int tot = 0;
    for (int i = 1; i < n; i++) tot += (h[i] != h[i + 1]), tot += (l[i] != l[i + 1]);
    for (int i = 1; i < n; i++)
        if (h[i + 1] > h[i])
            S[h[i]] = i;
        else if (h[i + 1] < h[i]) {
            if (S[h[i + 1]]) vec2.emplace_back(S[h[i + 1]], i);
            while (!S.empty() && S.rbegin()->first >= h[i + 1]) S.erase(--S.end());
        }
    S.clear();
    for (int i = 1; i < n; i++)
        if (l[i + 1] > l[i])
            S[l[i]] = i;
        else if (l[i + 1] < l[i]) {
            if (S[l[i + 1]]) vec2.emplace_back(S[l[i + 1]], i);
            while (!S.empty() && S.rbegin()->first >= l[i + 1]) S.erase(--S.end());
        }
    sort(vec2.begin(), vec2.end());
    int cnt = vec1.size() + vec2.size();
    for (int i = 0, j = 0; i < (int)vec1.size(); i++) {
        while (j < (int)vec2.size() && vec2[j].first <= vec1[i]) R.push(vec2[j++].second);
        while (!R.empty() && R.top() < vec1[i]) R.pop();
        if (!R.empty()) R.pop(), cnt--;
    }
    cout << tot - cnt << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}