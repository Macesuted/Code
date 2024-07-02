/**
 * @file 104772I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int n, k;
bool f[15];

int post(int l, int r) {
    cout << l << ' ' << r << endl;
    cin >> k;
    if (k == n) exit(0);
    return k;
}

void solve(void) {
    cin >> n >> k;
    if (k == n) return;
    auto check = [&](int p) {
        if (f[p]) return true;
        int v = k;
        post(p, p);
        if (v + 1 == k) return f[p] = true;
        if (v - 1 == k) return post(p, p), f[p] = true;
        return f[p] = false;
    };
    for (int i = 1; i <= n; i++) check(i);
    for (int i = 1; i <= n; i++)
        while (!f[i]) {
            int d = 1;
            while (i + d <= n && !f[i + d]) d++;
            bool stop = false;
            vector<int> SS;
            SS.push_back(0);
            for (int t = 0; t < d; t++)
                for (int i = (int)SS.size() - 1; ~i; i--) SS.push_back(SS[i] + (1 << t));
            for (int S = 1; S < (int)SS.size(); S++) {
                for (int j = 0; j < d; j++)
                    if ((SS[S] >> j & 1) != (SS[S - 1] >> j & 1)) {
                        int v = k;
                        post(i, i + j);
                        if (v != k) {
                            for (int t = i; t <= n; t++) check(t);
                            stop = true;
                            break;
                        }
                    }
                if (stop) break;
            }
        }
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