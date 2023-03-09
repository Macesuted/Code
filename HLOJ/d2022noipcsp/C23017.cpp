/**
 * @file C23017.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-07
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

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    int64_t sum[maxn << 2];
    int cnt[maxn << 2], n;

    void pushUp(int p) { return sum[p] = sum[p << 1] + sum[p << 1 | 1], cnt[p] = cnt[p << 1] + cnt[p << 1 | 1], void(); }
    void build(int p, int l, int r) {
        if (l == r) return sum[p] = cnt[p] = 0, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return cnt[p] += (v > 0 ? +1 : -1), sum[p] += v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int& x) {
        if (cnt[p] <= x) return x -= cnt[p], sum[p];
        int mid = (l + r) >> 1;
        int64_t ret = query(p << 1, l, mid, x);
        if (x) ret += query(p << 1 | 1, mid + 1, r, x);
        return ret;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int64_t query(int x) { return query(1, 1, n, x); }
} ST[2];

tiii a[maxn];
vector<pii> rec[maxn];

void solve(void) {
    int n;
    int64_t lim;
    cin >> n >> lim;
    ST[0].resize(n), ST[1].resize(n), ST[0].build(), ST[1].build();
    for (int i = 1; i <= n; i++) rec[i].clear();
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]), get<2>(a[i]) = i;
    sort(a + 1, a + n + 1, [&](tiii x, tiii y) { return get<0>(x) < get<0>(y); });
    for (int i = 1; i <= n; i++) rec[get<1>(a[i])].emplace_back(i, get<0>(a[i]));
    pii ans = {0, 0};
    int64_t sum = 0;
    for (int i = 1, cnt = 0, tot = 0; i <= n; i++) {
        sum += get<0>(a[i]);
        if (sum > lim) break;
        if (get<1>(a[i]) < i)
            cnt++, ST[0].update(i, -get<0>(a[i]));
        else
            ST[1].update(n - i + 1, get<0>(a[i]));
        tot += rec[i].size();
        for (auto j : rec[i])
            if (j.first <= i)
                cnt++, ST[1].update(n - j.first + 1, -j.second);
            else
                ST[0].update(j.first, j.second);
        int l = 0, r = min(i - cnt, tot - cnt) + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (sum + ST[0].query(mid) - ST[1].query(mid) <= lim ? l : r) = mid;
        }
        ans = max(ans, pii{cnt + l, i});
    }
    vector<int> vec;
    for (int i = 1, c = 1; i <= n && c <= ans.first; i++)
        if (get<1>(a[i]) <= ans.second) vec.push_back(get<2>(a[i])), c++;
    for (int i = 1, c = 1; i <= n && c <= ans.second - ans.first; i++)
        if (get<1>(a[i]) > ans.second) vec.push_back(get<2>(a[i])), c++;
    sort(vec.begin(), vec.end());
    cout << ans.first << endl;
    cout << ans.second << endl;
    for (auto i : vec) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("easy.in", "r", stdin), freopen("easy.out", "w", stdout);
#endif
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