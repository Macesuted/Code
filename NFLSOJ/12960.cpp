/**
 * @file wall.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

class UnionSet {
   private:
    int fa[maxn];

   public:
    void init(int l, int r) {
        for (int i = l - 1; i <= r + 1; i++) fa[i] = i;
        return;
    }
    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    void merge(int x, int y) { return fa[getfa(x)] = getfa(y), void(); }
} US[2];

string s[maxn];
int lef[maxn][maxn], rig[maxn][maxn], up[maxn][maxn], dow[maxn][maxn];
vector<int> rec[maxn];

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = " " + s[i];
    auto calcLef = [&](int x) {
        for (int j = 1, l = 1; j <= m; j++) {
            if (s[x][j] == '.') l = j + 1;
            lef[x][j] = l;
        }
        return;
    };
    auto calcRig = [&](int x) {
        for (int j = m, l = m; j; j--) {
            if (s[x][j] == '.') l = j - 1;
            rig[x][j] = l;
        }
        return;
    };
    auto calcUp = [&](int y) {
        for (int i = 1, l = 1; i <= n; i++) {
            if (s[i][y] == '.') l = i + 1;
            up[i][y] = l;
        }
        return;
    };
    auto calcDow = [&](int y) {
        for (int i = n, l = n; i; i--) {
            if (s[i][y] == '.') l = i - 1;
            dow[i][y] = l;
        }
        return;
    };
    for (int i = 1; i <= n; i++) calcLef(i), calcRig(i);
    for (int j = 1; j <= m; j++) calcUp(j), calcDow(j);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            s[x][y] = (s[x][y] == '#' ? '.' : '#');
            calcLef(x), calcRig(x), calcUp(y), calcDow(y);
        } else {
            int ans = 0;
            {
                US[0].init(up[x][y], dow[x][y]), US[1].init(up[x][y], dow[x][y]);
                for (int i = up[x][y]; i <= dow[x][y]; i++) rec[lef[i][y]].push_back(i);
                for (int i = y; i; i--) {
                    int l = US[0].getfa(max(up[x][y], up[x][i])), r = US[1].getfa(min(dow[x][y], dow[x][i]));
                    if (l <= x && x <= r) ans = max(ans, (r - l + 1) * (y - i + 1));
                    for (auto j : rec[i]) US[0].merge(j, j + 1), US[1].merge(j, j - 1);
                    rec[i].clear();
                }
            }
            {
                US[0].init(up[x][y], dow[x][y]), US[1].init(up[x][y], dow[x][y]);
                for (int i = up[x][y]; i <= dow[x][y]; i++) rec[rig[i][y]].push_back(i);
                for (int i = y; i <= m; i++) {
                    int l = US[0].getfa(max(up[x][y], up[x][i])), r = US[1].getfa(min(dow[x][y], dow[x][i]));
                    if (l <= x && x <= r) ans = max(ans, (r - l + 1) * (i - y + 1));
                    for (auto j : rec[i]) US[0].merge(j, j + 1), US[1].merge(j, j - 1);
                    rec[i].clear();
                }
            }
            {
                US[0].init(lef[x][y], rig[x][y]), US[1].init(lef[x][y], rig[x][y]);
                for (int i = lef[x][y]; i <= rig[x][y]; i++) rec[up[x][i]].push_back(i);
                for (int i = x; i; i--) {
                    int l = US[0].getfa(max(lef[x][y], lef[i][y])), r = US[1].getfa(min(rig[x][y], rig[i][y]));
                    if (l <= y && y <= r) ans = max(ans, (r - l + 1) * (x - i + 1));
                    for (auto j : rec[i]) US[0].merge(j, j + 1), US[1].merge(j, j - 1);
                    rec[i].clear();
                }
            }
            {
                US[0].init(lef[x][y], rig[x][y]), US[1].init(lef[x][y], rig[x][y]);
                for (int i = lef[x][y]; i <= rig[x][y]; i++) rec[dow[x][i]].push_back(i);
                for (int i = x; i <= n; i++) {
                    int l = US[0].getfa(max(lef[x][y], lef[i][y])), r = US[1].getfa(min(rig[x][y], rig[i][y]));
                    if (l <= y && y <= r) ans = max(ans, (r - l + 1) * (i - x + 1));
                    for (auto j : rec[i]) US[0].merge(j, j + 1), US[1].merge(j, j - 1);
                    rec[i].clear();
                }
            }
            cout << ans << endl;
        }
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("wall.in", "r", stdin), freopen("wall.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) rec[i].reserve(maxn);

    int _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ':' << endl, solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
