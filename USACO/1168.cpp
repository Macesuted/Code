/**
 * @file 1168.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

typedef pair<int, int> pii;

pii calc(vector<int>& a, vector<int>& b) {
    int cnt[2] = {0, 0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (a[i] != b[j]) cnt[a[i] > b[j]]++;
    return MP(cnt[0], cnt[1]);
}

void solve(void) {
    vector<int> a(4), b(4), c(4);
    for (int i = 0; i < 4; i++) cin >> a[i];
    for (int i = 0; i < 4; i++) cin >> b[i];
    for (c[0] = 1; c[0] <= 10; c[0]++)
        for (c[1] = 1; c[1] <= 10; c[1]++)
            for (c[2] = 1; c[2] <= 10; c[2]++)
                for (c[3] = 1; c[3] <= 10; c[3]++) {
                    pii ab = calc(a, b), ac = calc(a, c), bc = calc(b, c);
                    if (ab.first > ab.second && bc.first > bc.second && ac.second > ac.first ||
                        ac.first > ac.second && bc.second > bc.first && ab.second > ab.first ||
                        ab.second > ab.first && ac.first > ac.second && bc.second > bc.first ||
                        bc.first > bc.second && ac.second > ac.first && ab.first > ab.second ||
                        ac.second > ac.first && ab.first > ab.second && bc.first > bc.second ||
                        bc.second > bc.first && ab.second > ab.first && ac.first > ac.second)
                        return cout << "yes" << endl, void();
                }
    return cout << "no" << endl, void();
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
