/**
 * @file 126.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-13
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

int a[maxn], plen[maxn], qlen[maxn], len[maxn];
vector<pii> b, op;
vector<int> c;

int getPos(const vector<pii>& a, int p) {
    int sum = 0;
    for (int i = 0; i <= p; i++) sum += len[a[i].first];
    return sum;
}
bool dfs(const vector<pii>& tar, const vector<pii>& a, int k) {
    bool chk = true;
    for (int i = 0; i < (int)a.size() && chk; i++)
        chk &= !(tar[i].first != a[i].first || (tar[i].second && tar[i].second != a[i].second));
    if (chk) return true;
    if (!k) return false;
    for (int l = 0; l < (int)a.size(); l++)
        for (int r = l; r < (int)a.size(); r++) {
            vector<pii> b = a;
            for (int i = l; i <= r; i++) b[i] = a[l + r - i], b[i].second *= -1;
            op.emplace_back(getPos(a, l - 1) + 1, getPos(a, r));
            if (dfs(tar, b, k - 1)) return true;
            op.pop_back();
        }
    return false;
}
vector<pii> init(vector<pii> b) {
    c.clear();
    for (auto i : b) c.push_back(i.first);
    sort(c.begin(), c.end());
    for (auto& i : b) i.first = lower_bound(c.begin(), c.end(), i.first) - c.begin();
    for (int i = 0; i < (int)b.size(); i++) len[b[i].first] = qlen[i];
    return b;
}
vector<pii> gen(int n) {
    vector<pii> a;
    for (int i = 0; i < n; i++) a.emplace_back(i, 1);
    return a;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, j; i <= n; i = j + 1) {
        j = i, c.push_back(a[i]);
        if (j == n || abs(a[j] - a[j + 1]) != 1) {
            plen[b.size()] = qlen[b.size()] = 1, b.emplace_back(a[i], 0);
            continue;
        }
        int v = a[j + 1] - a[j];
        while (j < n && a[j + 1] - a[j] == v) j++;
        plen[b.size()] = qlen[b.size()] = j - i + 1, b.emplace_back(a[i], v);
    }
    if ((int)b.size() > 2 * k + 1) return cout << "NIE" << endl, void();
    if (dfs(init(b), gen(b.size()), k)) {
        cout << "TAK" << endl, reverse(op.begin(), op.end());
        while ((int)op.size() < k) op.emplace_back(1, 1);
        for (auto i : op) cout << i.first << ' ' << i.second << endl;
        cout << endl;
        return;
    }
    for (int S = 0; S < (1 << (int)b.size()); S++) {
        int tot = b.size();
        for (int i = 0; i < (int)b.size(); i++)
            if (S >> i & 1) tot += plen[i] - 1;
        if (tot > 2 * k + 1) continue;
        vector<pii> d;
        for (int i = 0; i < (int)b.size(); i++)
            if (S >> i & 1)
                for (int j = 0, v = b[i].first; j < plen[i]; j++, v += b[i].second)
                    qlen[d.size()] = 1, d.emplace_back(v, 0);
            else
                qlen[d.size()] = plen[i], d.push_back(b[i]);
        if (dfs(init(d), gen(d.size()), k)) {
            cout << "TAK" << endl, reverse(op.begin(), op.end());
            while ((int)op.size() < k) op.emplace_back(1, 1);
            for (auto i : op) cout << i.first << ' ' << i.second << endl;
            cout << endl;
            return;
        }
    }
    return cout << "NIE" << endl, void();
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("rev.in", "r", stdin), freopen("rev.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}