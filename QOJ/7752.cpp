/**
 * @file 7752.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class UnionSet {
   private:
    int fa[maxn];

    int getfa(int p) { return p == fa[p] ? p : fa[p] = getfa(fa[p]); }

   public:
    UnionSet(void) {
        for (int i = 0; i < maxn; i++) fa[i] = i;
    }

    bool merge(int x, int y) {
        x = getfa(x), y = getfa(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }
} US;

int ucnt = 0;
map<int, vector<pii>> S;
int cross(tiii x, tiii y) { return max(0, min(get<1>(x), get<1>(y)) - max(get<0>(x), get<0>(y)) + 1); }

bool solve(void) {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1, xl, xr, y; i <= k; i++) cin >> xl >> xr >> y, S[y].emplace_back(xl, xr);

    if (n == 1 || m == 1) return true;

    vector<tiii> lst;
    for (int i = 1; i <= m; i++) {
        vector<tiii> cur;
        if (!S.count(i))
            cur.emplace_back(1, n, ++ucnt);
        else {
            vector<pii> &vec = S[i];
            vec.emplace_back(0, 0), vec.emplace_back(n + 1, n + 1);
            sort(vec.begin(), vec.end());
            for (int j = 0; j + 1 < (int)vec.size(); j++)
                if (vec[j].second + 1 < vec[j + 1].first) cur.emplace_back(vec[j].second + 1, vec[j + 1].first - 1, ++ucnt);
        }
        for (auto x = lst.begin(), y = cur.begin(); x != lst.end() && y != cur.end(); y++) {
            while (x != lst.end() && get<1>(*x) < get<0>(*y)) x++;
            while (x != lst.end() && get<1>(*x) <= get<1>(*y)) {
                if (cross(*x, *y) > 1 || !US.merge(get<2>(*x), get<2>(*y))) return false;
                x++;
            }
            if (x != lst.end() && cross(*x, *y))
                if (cross(*x, *y) > 1 || !US.merge(get<2>(*x), get<2>(*y))) return false;
        }
        lst = cur;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

    return 0;
}