/**
 * @file 14301.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

using pii = pair<int, int>;
using tscis = tuple<string, char, int, string>;

struct Team {
    int wa[26];
    int cnt, tim;
    int unknownCnt, unknownTim;
    Team(void) {
        for (int i = 0; i < 26; i++) wa[i] = 0;
        cnt = tim = unknownCnt = unknownTim = 0;
    }
};

tscis a[maxn];

void solve(void) {
    map<string, Team> rec;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string name;
        char id;
        int tim;
        string res;
        cin >> name >> id >> tim >> res;
        a[i] = {name, id, tim, res};
    }

    sort(a + 1, a + n + 1, [](const tscis &x, const tscis &y) { return get<2>(x) < get<2>(y); });

    for (int i = 1; i <= n; i++) {
        auto [name, id, tim, res] = a[i];
        Team &o = rec[name];
        if (o.wa[id - 'A'] == -1) continue;
        if (res == "Accepted") {
            o.cnt++;
            o.tim += tim + rec[name].wa[id - 'A'] * 20;
            o.wa[id - 'A'] = -1;
        } else if (res == "Unknown") {
            o.unknownCnt++;
            o.unknownTim += tim + rec[name].wa[id - 'A'] * 20;
            o.wa[id - 'A'] = -1;
        } else if (o.wa[id - 'A'] != -1)
            o.wa[id - 'A']++;
    }

    pii best = {0, 0};
    for (auto &[name, o] : rec) best = max(best, {o.cnt, -o.tim});

    for (auto &[name, o] : rec)
        if (pii{o.cnt + o.unknownCnt, -o.tim - o.unknownTim} >= best) cout << name << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
