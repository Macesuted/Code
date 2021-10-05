/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

int a[maxn], p[maxn], cnt[maxn];
vector<vector<int> > rec;
set<int> S;

inline bool cmp(int x, int y) { return cnt[x] < cnt[y]; }

void work(void) {
    int n;
    cin >> n;
    rec.resize(n + 1);
    for (register int i = 1; i <= n; i++) cnt[i] = 0;
    for (register int i = 1; i <= n; i++) cin >> a[i], rec[a[i]].push_back(i), cnt[a[i]]++, p[i] = 0, S.insert(i);
    int ans = 0;
    for (register int i = 1; i <= n; i++)
        if (!rec[i].empty()) {
            sort(rec[i].begin(), rec[i].end(), cmp);
            p[rec[i][0]] = i;
            ans++;
            S.erase(i);
        }
    static vector<int> rest;
    rest.clear();
    for (register int i = 1; i <= n; i++)
        if (!p[i] && S.count(i)) rest.push_back(i), S.erase(i);
    if (rest.size() == 1)
        p[rest[0]] = *S.begin(), S.erase(S.begin()), S.insert(rest[0]);
    else
        for (register int i = 0; i < rest.size(); i++) p[rest[i]] = rest[(i + 1) % rest.size()];
    for (register int i = 1; i <= n; i++)
        if (!p[i]) {
            set<int>::iterator it = S.begin();
            while (*it == i) it++;
            p[i] = *it, S.erase(it);
        }
    cout << ans << endl;
    for (register int i = 1; i <= n; i++) cout << p[i] << ' ';
    cout << endl;
    rec.clear(), S.clear();
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}
