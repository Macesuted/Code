/**
 * @file 7522.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 300005

class UnionSet {
   private:
    unordered_map<int, int> fa;

    int getfa(int p) { return p == fa[p] ? p : fa[p] = getfa(fa[p]); }

   public:
    bool query(int x, int y) {
        if (!fa.count(x) || !fa.count(y)) return false;
        x = getfa(x), y = getfa(y);
        return x == y;
    }
    void merge(int x, int y) {
        if (!fa.count(x)) fa[x] = x;
        if (!fa.count(y)) fa[y] = y;
        x = getfa(x), y = getfa(y);
        if (x != y) fa[x] = y;
        return;
    }
};

vector<UnionSet *> US;
int ans[maxn], cnt[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    US.clear(), US.push_back(new UnionSet());
    for (int i = 1; i <= m; i++) ans[i] = cnt[i] = 0;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        int l = 0, r = US.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (US[mid]->query(x, y) ? l : r) = mid;
        }
        if (r == (int)US.size()) US.push_back(new UnionSet());
        US[r]->merge(x, y), cnt[ans[i] = r]++;
    }
    for (int i = 1; i <= m; i++) cout << (cnt[ans[i]] == n - 1 ? ans[i] : -1) << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}