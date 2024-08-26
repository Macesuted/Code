/**
 * @file A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 5005

typedef pair<int, int> pii;

pii a[maxn];

int64_t dis(pii x, pii y) { return abs(x.first - y.first) + abs(x.second - y.second); }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    vector<pii> answer;
    while (true) {
        bool chk = true;
        for (int i = 2; i <= n; i++) chk &= (a[1] == a[i]);
        if (chk) break;
        int p = 2;
        while (a[p] == a[1]) p++;
        for (int i = p + 1; i <= n; i++)
            if (a[1] != a[i] && dis(a[i], a[1]) < dis(a[p], a[1])) p = i;
        if (a[1].first > a[p].first) swap(a[1], a[p]);
        int tx = (a[1].first + a[p].first) / 2, ty = (a[1].second + a[p].second) / 2;
        if (abs(a[1].first - tx) > abs(a[p].first - tx)) tx--;
        if (abs(a[1].second - ty) < abs(a[p].second - ty)) ty += (ty < a[p].second ? +1 : -1);
        int tot = min(abs(a[1].first - tx) + abs(a[1].second - ty), abs(a[p].first - tx) + abs(a[p].second - ty)) + 1;
        for (int i = 1; i <= n; i++) {
            int dx = abs(a[i].first - tx), dy = abs(a[i].second - ty), tim = tot;
            if (tim >= dx)
                a[i].first = tx, tim -= dx;
            else
                a[i].first += (a[i].first < tx ? +tim : -tim), tim = 0;
            if (tim >= dy)
                a[i].second = ty, tim -= dy;
            else
                a[i].second += (a[i].second < ty ? +tim : -tim), tim = 0;
        }
        answer.emplace_back(tx, ty);
    }
    cout << answer.size() << endl;
    for (auto [x, y] : answer) cout << x << ' ' << y << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}