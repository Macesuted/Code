/**
 * @file 15487.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using Chain = list<int>;

deque<pair<Chain *, Chain *>> que[2];

void solve(void) {
    int n, k, d, q;
    cin >> n >> k >> d >> q;

    vector<pair<Chain *, Chain *>> cA(d);
    for (int i = 0; i < d; i++) cA[i] = {new Chain(), new Chain()};
    for (int i = 0, j = 0; i < n; i++, j = (j + 1) % d) ((int)cA[j].first->size() < k ? cA[j].first : cA[j].second)->push_back(i);

    for (auto v : cA) que[0].push_back(v);

    vector<pair<Chain *, Chain *>> cB(d);
    for (int i = 0; i < d; i++) cB[i] = {new Chain(), new Chain()};
    cB[0].first = cA[0].first;
    for (int len = 0, i = 0, v = n; v < 2 * n - k; len += (i == d - 1), i = (i + 1) % d) {
        if (!i && len < k) continue;
        (len < k ? cB[i].first : cB[i].second)->push_back(v++);
    }
    for (auto v : cB) que[1].push_back(v);

    while (q--) {
        char c;
        cin >> c;
        bool t = (c == 'A');

        int id = (n - 1) % d;
        int tail;
        if (!que[t][id].second->empty())
            tail = que[t][id].second->back(), que[t][id].second->pop_back();
        else
            tail = que[t][id].first->back(), que[t][id].first->pop_back();

        que[t].push_front(que[t].back()), que[t].pop_back();
        que[t].front().first->push_front(tail);
        if ((int)que[t].front().first->size() > k)
            que[t].front().second->push_front(que[t].front().first->back()), que[t].front().first->pop_back();

        que[!t].front().first = que[t].front().first;
    }

    for (int t = 0; t < 2; t++) {
        vector<int> rec(n);
        for (int i = 0; i < d; i++) {
            int j = i;
            for (auto v : *que[t][i].first) rec[j] = v, j += d;
            for (auto v : *que[t][i].second) rec[j] = v, j += d;
        }

        int64_t ans = 0;
        for (int i = 0; i < n; i++) ans += (int64_t)i * rec[i];
        cout << ans << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
