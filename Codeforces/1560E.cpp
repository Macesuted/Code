/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

int cnt[26];
string rec[26];
bool vis[26];

void work(void) {
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    string t;
    memset(vis, 0, sizeof(vis));
    for (register int i = n; i; i--)
        if (!vis[s[i] - 'a']) vis[s[i] - 'a'] = true, t = s[i] + t;
    memset(cnt, 0, sizeof(cnt));
    for (register int i = 1; i <= n; i++) cnt[s[i] - 'a']++;
    int tot = 0;
    for (register int i = t.size(); i; i--) {
        int c = t[i - 1] - 'a';
        if (cnt[c] % i != 0) return cout << -1 << endl, void();
        tot += (cnt[c] /= i);
    }
    string pre;
    for (register int i = 1; i <= tot; i++) pre.push_back(s[i]);
    for (register int i = 1, p = 1; i <= (int)t.size(); i++) {
        if (p > n) return cout << -1 << endl, void();
        for (register int j = 0; j < (int)pre.size() && p + j <= n; j++)
            if (pre[j] != s[p + j]) return cout << -1 << endl, void();
        p += pre.size();
        string tat;
        for (register int j = 0; j < (int)pre.size(); j++)
            if (pre[j] != t[i - 1]) tat.push_back(pre[j]);
        pre = tat;
    }
    for (register int i = 1; i <= tot; i++) cout << s[i];
    cout << ' ' << t << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}