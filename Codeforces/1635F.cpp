/**
 * @file 1635F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-07
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

#define maxn 300005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int64_t> tiil;

class FenwickTree {
   private:
    int64_t tree[maxn];

   public:
    FenwickTree(void) { memset(tree, 0x3f, sizeof(tree)); }
    void add(int p, int64_t v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] = min(tree[i], v);
        return;
    }
    int64_t query(int p) {
        int64_t sum = INT64_MAX;
        for (int i = p; i; i -= i & -i) sum = min(sum, tree[i]);
        return sum;
    }
} FT;

pii a[maxn];
tiii ques[maxn];
int64_t ans[maxn];
vector<tiil> node;
stack<int> S;

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 1; i <= n; i++) {
        while (!S.empty() && a[S.top()].second > a[i].second) S.pop();
        if (!S.empty())
            node.emplace_back(S.top(), i, 1LL * abs(a[i].first - a[S.top()].first) * (a[i].second + a[S.top()].second));
        S.push(i);
    }
    while (!S.empty()) S.pop();
    for (int i = n; i; i--) {
        while (!S.empty() && a[S.top()].second > a[i].second) S.pop();
        if (!S.empty())
            node.emplace_back(i, S.top(), 1LL * abs(a[i].first - a[S.top()].first) * (a[i].second + a[S.top()].second));
        S.push(i);
    }
    while (!S.empty()) S.pop();
    for (int i = 1; i <= q; i++) cin >> get<0>(ques[i]) >> get<1>(ques[i]), get<2>(ques[i]) = i;
    sort(node.begin(), node.end()), sort(ques + 1, ques + q + 1);
    for (int i = n, j = (int)node.size() - 1, k = q; i; i--) {
        while (~j && get<0>(node[j]) == i) FT.add(get<1>(node[j]), get<2>(node[j])), j--;
        while (k && get<0>(ques[k]) == i) ans[get<2>(ques[k])] = FT.query(get<1>(ques[k])), k--;
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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