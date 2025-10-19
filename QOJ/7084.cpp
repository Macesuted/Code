/**
 * @file 7084.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int64_t f[105][205][205];

void solve(void) {
    int64_t Ha, Hb, Hc, Aa, Ab, Ac;
    cin >> Ha >> Hb >> Hc >> Aa >> Ab >> Ac;

    for (int i = 0; i <= 101; i++)
        for (int ha = 0; ha < 205; ha++)
            for (int hb = 0; hb < 205; hb++) f[i][ha][hb] = INT64_MAX;

    f[0][0][0] = 0;
    for (int i = 1; i <= 101; i++) {
        for (int ha = 0; ha < 205; ha++)
            for (int hb = 0; hb < 205; hb++) {
                if (f[i - 1][ha][hb] == INT64_MAX) continue;
                int64_t w = f[i - 1][ha][hb];
                if (ha < Ha) w += Aa;
                if (hb < Hb) w += Ab;
                if (int64_t(i - 1) * i / 2 - ha - hb < Hc) w += Ac;

                if (ha < Ha) f[i][ha + i][hb] = min(f[i][ha + i][hb], w);
                if (hb < Hb) f[i][ha][hb + i] = min(f[i][ha][hb + i], w);
                if (int64_t(i - 1) * i / 2 - ha - hb < Hc) f[i][ha][hb] = min(f[i][ha][hb], w);
            }
    }

    auto calc = [&](int64_t v) -> int64_t {
        int64_t l = 0, r = 2e9;
        while (l + 1 < r) {
            int64_t mid = (l + r) >> 1;
            (mid * (mid + 1) / 2 >= v ? r : l) = mid;
        }
        return r;
    };

    int64_t ans = INT64_MAX;
    for (int ha = Ha; ha < 205; ha++)
        for (int hb = Hb; hb < 205; hb++) {
            int64_t v = calc(ha + hb + Hc);
            for (int i = 0; i <= 101; i++)
                if (f[i][ha][hb] != INT64_MAX) ans = min(ans, f[i][ha][hb] + (v - i) * Ac);
        }

    for (int ha = Ha; ha < 205; ha++) {
        if (f[100][ha][0] == INT64_MAX) continue;

        int64_t v = calc(ha + Hc);
        ans = min(ans, f[100][ha][0] + (v - 100) * (Ab + Ac) + Ab);
    }

    for (int hb = Hb; hb < 205; hb++) {
        if (f[100][0][hb] == INT64_MAX) continue;

        int64_t v = calc(hb + Hc);
        ans = min(ans, f[100][0][hb] + (v - 100) * (Aa + Ac) + Aa);
    }

    int64_t v = calc(Hc);
    if (f[100][0][0] != INT64_MAX) ans = min(ans, f[100][0][0] + (v - 100) * (Aa + Ab + Ac) + max(Aa, Ab) + 2 * min(Aa, Ab));

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
