/**
 * @file 7680.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

map<int, vector<int>> rec;
map<int, vector<pii>> ques;
set<pii> S;
int ans[maxn];

int find(int p) {
    auto pt = S.lower_bound({p, 0});
    if (pt != S.begin() && (--pt)->second < p) pt++;
    return max(p, pt->first);
}
void insert(int p) {
    if (find(p) == p) return;
    int l = p, r = p;
    auto pt = S.lower_bound({p, 0});
    if (pt != S.end() && pt->first == p + 1) r = pt->second, pt = S.erase(pt);
    if (pt != S.begin() && (--pt)->second == p - 1) l = pt->first, S.erase(pt);
    return S.emplace(l, r), void();
}
void erase(int p, int x) {
    auto pt = S.lower_bound({p, 0});
    if (pt != S.begin() && (--pt)->second < p) pt++;
    int l = pt->first, r = pt->second;
    S.erase(pt);
    if (l < p) S.emplace(l, p - 1), l = p;
    pt = S.emplace(l, r).first;
    while (pt->second - pt->first + 1 <= x) x -= pt->second - pt->first + 1, pt = S.erase(pt);
    if (x) tie(l, r) = *pt, S.erase(pt), S.emplace(l + x, r);
    return;
}

void solve(void) {
    rec.clear(), ques.clear(), S.clear(), S.emplace(0, 2e9);
    int n, q;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) cin >> x >> y, rec[x].push_back(y);
    for (auto &i : rec) i.second.push_back(-1), i.second.push_back(2e9), sort(i.second.begin(), i.second.end());
    cin >> q;
    for (int i = 1, x, y; i <= q; i++) cin >> x >> y, ques[x].emplace_back(y, i);
    for (int i = 0; i <= 10; i++) ques[i].emplace_back(0, 0);
    int last = -1;
    auto j = rec.begin();
    for (auto &i : ques) {
        int p = i.first;
        set<int> pts;
        while (j != rec.end() && j->first <= p) {
            erase(0, j->first - 1 - last), pts.clear();
            for (int k = 0; k + 1 < (int)j->second.size(); k++) {
                int x = find(j->second[k] + 1);
                if (x < j->second[k + 1]) erase(x, 1), pts.insert(x);
                if (~j->second[k]) insert(j->second[k]);
            }
            last = (j++)->first;
        }
        if (last != p) erase(0, p - 1 - last), pts.clear(), pts.insert(find(0)), erase(*pts.begin(), 1), last = p;
        for (auto j : i.second) ans[j.second] = !pts.count(j.first);
    }
    for (int i = 1; i <= q; i++) cout << (ans[i] ? "Alice" : "Bob") << endl;
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