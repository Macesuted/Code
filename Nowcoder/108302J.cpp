/**
 * @file 108302J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int way[4][2] = {{0, +1}, {0, -1}, {+1, 0}, {-1, 0}};

using pii = pair<int, int>;

vector<vector<int>> a;
int n, m;

bool chk(int lim) {
    int mxl = 1, mxr = n + m, myl = 1, myr = n + m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] <= lim) continue;
            int x = i + (m + 1 - j), y = i + j;
            mxl = max(mxl, x - lim), mxr = min(mxr, x + lim);
            myl = max(myl, y - lim), myr = min(myr, y + lim);
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x = i + (m + 1 - j), y = i + j;
            if (mxl <= x && x <= mxr && myl <= y && y <= myr) return true;
        }

    return false;
}

void solve(void) {
    cin >> n >> m;
    a.resize(n + 1, vector<int>(m + 1));

    queue<pii> que;
    for (int i = 1; i <= n; i++)
        for (int j = 1, x; j <= m; j++) {
            cin >> x;
            if (x == 1)
                a[i][j] = 0, que.emplace(i, j);
            else
                a[i][j] = INT_MAX;
        }

    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int t = 0; t < 4; t++) {
            int tx = x + way[t][0], ty = y + way[t][1];
            if (1 <= tx && tx <= n && 1 <= ty && ty <= m && a[tx][ty] > a[x][y] + 1)
                a[tx][ty] = a[x][y] + 1, que.emplace(tx, ty);
        }
    }

    int l = -1, r = n + m;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }

    cout << r << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
