/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 * @brief My Solution: https://www.macesuted.cn/article/cf1521c/
 */

#include <bits/stdc++.h>
using namespace std;

int ask1(int i, int j, int p) {
    cout << "? 1 " << i << ' ' << j << ' ' << p << endl;
    int ret;
    cin >> ret;
    return ret;
}
int ask2(int i, int j, int p) {
    cout << "? 2 " << i << ' ' << j << ' ' << p << endl;
    int ret;
    cin >> ret;
    return ret;
}

int p[10005];
bool vis[10005];

signed main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        for (register int i = 1; i <= n; i++) vis[i] = false;
        for (register int i = 1; i < n; i += 2) {
            int ret = ask1(i, i + 1, n - 1);
            p[i] = (ret == n - 1 && ask2(i, i + 1, n - 1) == n) ? n : ret;
            ret = ask2(i, i + 1, 1);
            p[i + 1] = (ret == 2 && ask1(i, i + 1, 1) == 1) ? 1 : ret;
            if (ask1(i, i + 1, p[i + 1]) == p[i + 1] + 1) swap(p[i], p[i + 1]);
            vis[p[i]] = vis[p[i + 1]] = true;
        }
        if (n & 1)
            for (register int i = 1; i <= n; i++)
                if (!vis[i]) p[n] = i;
        cout << '!';
        for (register int i = 1; i <= n; i++) cout << ' ' << p[i];
        cout << endl;
    }
    return 0;
}