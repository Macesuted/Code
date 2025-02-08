/**
 * @file 100200G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
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
typedef tuple<int, int, int> tiii;

string name[maxn];
double psum[maxn];
int pcnt[maxn];

int ac[maxn][26], rnk[maxn];
tiii score[maxn];
double S[maxn];

void solve(void) {
    int n, ML = 0;
    cin >> n, getline(cin, name[0]);
    for (int i = 1; i <= n; i++) getline(cin, name[i]), ML = max(ML, (int)name[i].size());
    for (int i = 1; i <= n; i++) name[i].resize(ML, ' ');

    int T;
    cin >> T;
    while (T--) {
        int k, A, B;
        cin >> k, A = 2 * k - 2, B = k - 2;

        vector<int> ptcp;
        for (int i = 1, t; i <= k; i++) cin >> t, ptcp.push_back(t);

        for (int i = 1; i <= n; i++) {
            score[i] = {0, 0, i};
            for (int j = 0; j < 26; j++) ac[i][j] = 0;
        }

        int m, q;
        cin >> m >> q;

        while (q--) {
            int tid, clk;
            char pc, stat;
            cin >> tid >> pc >> clk >> stat;
            if (ac[tid][pc - 'A'] > 0) continue;
            ac[tid][pc - 'A']--;
            if (stat == '+')
                ac[tid][pc - 'A'] *= -1, get<0>(score[tid])++, get<1>(score[tid]) += clk + 20 * (ac[tid][pc - 'A'] - 1);
        }

        sort(score + 1, score + n + 1, [](const tiii &a, const tiii &b) {
            return get<0>(a) != get<0>(b) ? get<0>(a) > get<0>(b) : get<1>(a) < get<1>(b);
        });

        for (int l = 1, r; l <= n; l = r + 1) {
            r = l;
            while (r < n && get<0>(score[l]) == get<0>(score[r + 1]) && get<1>(score[l]) == get<1>(score[r + 1])) r++;
            for (int i = l; i <= r; i++) rnk[i] = l;
        }

        int PM = get<0>(score[1]);
        for (int i = 1; i <= n; i++) S[get<2>(score[i])] = (PM ? 1. * get<0>(score[i]) / PM : 0.) * A / (rnk[i] + B);

        for (auto i : ptcp) pcnt[i]++, psum[i] += S[i];
    }

    vector<int> ids;
    for (int i = 1; i <= n; i++) ids.push_back(i), psum[i] = (pcnt[i] ? psum[i] / pcnt[i] : 0);

    sort(ids.begin(), ids.end(), [&](int x, int y) { return psum[x] > psum[y]; });

    cout << setprecision(4);
    for (auto i : ids) cout << name[i] << ' ' << fixed << psum[i] << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("ranking.in", "r", stdin), freopen("ranking.out", "w", stdout);
#endif
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