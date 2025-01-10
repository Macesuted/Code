/**
 * @file 884F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 105

typedef pair<int, int> pii;

int a[maxn];
pii cnt[maxn];

void solve(void) {
    int n;
    string s;
    cin >> n >> s, s = ' ' + s;
    int ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], ans += a[i];

    char c = '\0';
    for (int i = 0; i < 26; i++) cnt[i] = {0, i};
    for (int i = 1, j = n; i < j; i++, j--)
        if (s[i] == s[j]) ans -= min(a[i], a[j]), cnt[s[i] - 'a'].first++;

    sort(cnt, cnt + 26, greater<pii>());
    int sum = 0;
    for (int i = 1; i < 26; i++) sum += cnt[i].first;

    if (cnt[0].first > sum) {
        c = 'a' + cnt[0].second;
        vector<int> rec;
        for (int i = 1, j = n; i < j; i++, j--)
            if (s[i] != s[j] && c != s[i] && c != s[j]) rec.push_back(min(a[i], a[j]));
        sort(rec.begin(), rec.end());
        for (int i = 0; i < cnt[0].first - sum; i++) ans -= rec[i];
    }

    cout << ans << endl;

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