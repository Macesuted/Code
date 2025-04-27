/**
 * @file 2068F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

vector<int> rec[26];
string s[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        reverse(s[i].begin(), s[i].end());
        rec[s[i].back() - 'a'].push_back(i);
    }
    string t, ans;
    cin >> t;
    reverse(t.begin(), t.end());
    while (n) {
        int p = -1;
        for (int x = 0; x < 26; x++)
            if (t.back() - 'a' != x && !rec[x].empty()) p = x;
        if (p == -1) {
            p = t.back() - 'a';
            t.pop_back();
            if (t.empty()) return cout << "NO" << endl, void();
        }
        ans.push_back(p + 'a');
        vector<int> rrec;
        rrec.swap(rec[p]);
        for (auto idx : rrec) {
            s[idx].pop_back();
            if (s[idx].empty())
                n--;
            else
                rec[s[idx].back() - 'a'].push_back(idx);
        }
    }
    cout << "YES" << endl << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}