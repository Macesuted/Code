/**
 * @file 105789I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-20
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

#define maxn 1000005

int a[maxn], lef[maxn], rig[maxn];
bool avai[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i], avai[a[i]] = true;
    for (int i = 0; i < n; i++) rig[a[i]] = a[(i + 1) % n], lef[a[(i + 1) % n]] = a[i];
    int q;
    cin >> q;
    while (q--) {
        char op;
        cin >> op;
        if (op == '-') {
            int x;
            cin >> x;
            avai[x] = false;
            rig[lef[x]] = rig[x], lef[rig[x]] = lef[x];
        } else if (op == '+') {
            int x, p;
            cin >> x >> p;
            avai[x] = true;
            lef[x] = lef[p], rig[x] = p;
            rig[lef[x]] = lef[rig[x]] = x;
        } else {
            int len;
            cin >> len;
            vector<int> a(2 * len);
            for (int i = 0; i < len; i++) cin >> a[i], a[i + len] = a[i];
            int ans = 0;
            for (int l = 0, r; l < 2 * len; l = r + 1) {
                r = l;
                if (!avai[a[l]]) continue;
                while (r + 1 < 2 * len && avai[a[r + 1]] && rig[a[r]] == a[r + 1]) r++;
                ans = max(ans, r - l + 1);
            }
            if (ans > len)
                cout << '*' << endl;
            else
                cout << ans << endl;
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