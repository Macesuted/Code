/**
 * @file 1753E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-26
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

#define maxn 1000005

vector<vector<int64_t>> a, pre;
map<int, vector<int>> rec;
int val[maxn];
bool ban[maxn];
int64_t MUL = 1, ANS = 0;
int n, B, P, M, cnt = 0;

int check(int64_t lim) {
    int64_t lef = 1, rig = MUL;
    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (!ban[i]) lef *= val[i], rig /= val[i];
        if (a[i].empty() || lef == 1) continue;
        int64_t v = lim / (lef - 1) / rig + (lim % ((lef - 1) * rig) > 0);
        ans += upper_bound(a[i].begin(), a[i].end(), v, greater<int64_t>()) - a[i].begin();
    }
    return ans;
}

void dfs(auto p, int rest, int rig = 0) {
    if (p == rec.end()) {
        int x = rest / P;
        int64_t l = 0, r = INT64_MAX;
        while (l + 1 < r) {
            int64_t mid = l + ((r - l) >> 1);
            (check(mid) <= x ? r : l) = mid;
        }
        int64_t lef = 1, rig = MUL, ans = rig * (a[0].empty() ? 1 : pre[0].back() + 1);
        for (int i = 1; i <= cnt; i++) {
            if (!ban[i]) lef *= val[i], rig /= val[i];
            if (a[i].empty()) continue;
            ans += pre[i].back() * rig;
            if (lef == 1) continue;
            int64_t v = r / (lef - 1) / rig + (r % ((lef - 1) * rig) > 0);
            int c = upper_bound(a[i].begin(), a[i].end(), v, greater<int64_t>()) - a[i].begin();
            if (c) ans += pre[i][c - 1] * (lef - 1) * rig;
        }
        ANS = max(ANS, ans + (x - check(r)) * l);
        return;
    }
    auto np = p;
    for (auto i : p->second) ban[i] = false;
    auto x = p->second.begin();
    while (x != p->second.end() && *x < rig && rest >= 0) ban[*x] = true, rest -= M, x++;
    if (rest >= 0) dfs(++np, rest, rig);
    while (x != p->second.end() && rest >= M) ban[*x] = true, dfs(np, rest -= M, *x), x++;
    return;
}

void solve(void) {
    cin >> n >> B >> P >> M;
    a.push_back(vector<int64_t>());
    for (int i = 1; i <= n; i++) {
        char c;
        int x;
        cin >> c >> x;
        if (c == '+')
            a.back().push_back(x);
        else if (x != 1)
            cnt++, rec[val[cnt] = x].push_back(cnt), a.push_back(vector<int64_t>()), MUL *= x;
    }
    for (auto &i : a) sort(i.begin(), i.end(), greater<int64_t>());
    pre = a;
    for (auto &i : pre)
        for (auto j = 1; j < (int)i.size(); j++) i[j] += i[j - 1];
    dfs(rec.begin(), B);
    cout << ANS << endl;
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