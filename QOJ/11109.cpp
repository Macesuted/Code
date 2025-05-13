/**
 * @file 11109.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-13
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

#define maxn 300005
#define maxsqrtn 600

using tiii = tuple<int, int, int>;

vector<tiii> upds[maxn];
int64_t ans[maxsqrtn];
int bel[maxn], ql[maxn], qr[maxn], a[maxn], delt[maxsqrtn], add[maxsqrtn];
deque<int> cnt[maxsqrtn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x1, x2, y1, y2; i <= n; i++) {
        cin >> x1 >> x2 >> y1 >> y2;
        upds[x1].emplace_back(y1, y2 - 1, +1), upds[x2].emplace_back(y1, y2 - 1, -1);
    }

    int B = sqrt(n), Bcnt = 0;
    while (qr[Bcnt] < n) Bcnt++, ql[Bcnt] = qr[Bcnt - 1] + 1, qr[Bcnt] = min(qr[Bcnt - 1] + B, n);

    for (int i = 1; i <= Bcnt; i++) {
        cnt[i].push_back(0);
        for (int j = ql[i]; j <= qr[i]; j++) cnt[bel[j] = i][a[j] = 0]++;
    }

    for (int t = 1; t <= n; t++) {
        for (auto [l, r, v] : upds[t]) {
            if (bel[l] == bel[r]) {
                cnt[bel[l]].push_front(0), cnt[bel[l]].push_back(0), delt[bel[l]]--;
                for (int i = l; i <= r; i++) cnt[bel[i]][a[i] - delt[bel[l]]]--, a[i] += v, cnt[bel[i]][a[i] - delt[bel[l]]]++;
                continue;
            }

            cnt[bel[l]].push_front(0), cnt[bel[l]].push_back(0), delt[bel[l]]--;
            for (int i = l; i <= qr[bel[l]]; i++)
                cnt[bel[i]][a[i] - delt[bel[i]]]--, a[i] += v, cnt[bel[i]][a[i] - delt[bel[i]]]++;

            for (int t = bel[l] + 1; t < bel[r]; t++) add[t] += v;

            cnt[bel[r]].push_front(0), cnt[bel[r]].push_back(0), delt[bel[r]]--;
            for (int i = ql[bel[r]]; i <= r; i++)
                cnt[bel[i]][a[i] - delt[bel[i]]]--, a[i] += v, cnt[bel[i]][a[i] - delt[bel[i]]]++;
        }
        for (int b = 1; b <= Bcnt; b++) {
            while (cnt[b].front() == 0) cnt[b].pop_front(), delt[b]++;
            while (cnt[b].back() == 0) cnt[b].pop_back();
        }

        for (int b = 1; b <= Bcnt; b++)
            for (int v = (delt[b] + add[b] - 1) / m + 1; m * v - delt[b] - add[b] < (int)cnt[b].size(); v++)
                ans[v] += cnt[b][m * v - delt[b] - add[b]];
    }

    for (int i = 1; i <= n / m; i++) cout << ans[i] << endl;

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