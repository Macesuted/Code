/**
 * @file 7517.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef tuple<int64_t, int64_t, int64_t, int> tllli;

class FenwickTree {
   private:
    vector<int64_t> tree;
    int n;

   public:
    void resize(int _n) { return tree.resize((n = _n) + 1, 0); }
    void add(int p, int64_t v) {
        for (int i = p; i <= n; i += i & -i) tree[i] += v;
        return;
    }
    int64_t sum(int p) {
        int64_t sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};

tllli a[maxn];
int pos[maxn];
vector<tllli> F[maxn][2];

bool cmp(tllli a, tllli b) {
    if (!get<0>(b) && !get<1>(b)) return false;
    if (!get<0>(a) && !get<1>(a)) return true;
    return get<0>(a) * get<1>(b) > get<1>(a) * get<0>(b);
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]), get<2>(a[i]) = get<0>(a[i]) * get<1>(a[i]);
    for (int i = 0; i <= n + 1; i++) F[i][0].clear(), F[i][1].clear();
    vector<tllli> cac;
    stack<tllli> S;
    for (int i = 1; i <= n; i++) {
        tllli cur = a[i];
        while (!S.empty() && cmp(cur, S.top())) {
            cur = {get<0>(cur) + get<0>(S.top()), get<1>(cur) + get<1>(S.top()),
                   get<2>(cur) + get<2>(S.top()) + get<0>(S.top()) * get<1>(cur), 0};
            F[i][1].push_back(S.top()), S.pop();
        }
        get<3>(cur) = cac.size(), S.push(cur), F[i][0].push_back(cur), cac.push_back(cur);
    }
    while (!S.empty()) F[n + 1][1].push_back(S.top()), S.pop();
    for (int i = n; i; i--) {
        tllli cur = a[i];
        while (!S.empty() && cmp(cur, S.top())) {
            cur = {get<0>(cur) + get<0>(S.top()), get<1>(cur) + get<1>(S.top()),
                   get<2>(cur) + get<2>(S.top()) + get<0>(S.top()) * get<1>(cur), 0};
            F[i][0].push_back(S.top()), S.pop();
        }
        get<3>(cur) = cac.size(), S.push(cur), F[i][1].push_back(cur), cac.push_back(cur);
    }
    while (!S.empty()) F[0][0].push_back(S.top()), S.pop();

    sort(cac.begin(), cac.end(), cmp);
    for (int i = 0; i < (int)cac.size(); i++) pos[get<3>(cac[i])] = i + 1;

    FenwickTree Fa, Fb;
    Fa.resize(cac.size()), Fb.resize(cac.size());
    int64_t ans = 0, tot = 0;
    for (int i = 0; i <= n + 1; i++) {
        for (auto v : F[i][0]) {
            int p = pos[get<3>(v)];
            tot += Fa.sum(p - 1) * get<1>(v) + (Fb.sum(cac.size()) - Fb.sum(p)) * get<0>(v) + get<2>(v);
            Fa.add(p, get<0>(v)), Fb.add(p, get<1>(v));
        }
        for (auto v : F[i][1]) {
            int p = pos[get<3>(v)];
            Fa.add(p, -get<0>(v)), Fb.add(p, -get<1>(v));
            tot -= Fa.sum(p - 1) * get<1>(v) + (Fb.sum(cac.size()) - Fb.sum(p)) * get<0>(v) + get<2>(v);
        }
        ans = max(ans, tot);
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}