/**
 * @file 11967.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef MACESUTED

bool mem1;

#endif

class KingdomAndTrees {
#define maxn 55

   private:
    vector<int> heights;

    bool check(int lim) {
        int last = 0;
        for (auto i : heights)
            if (last + 1 - lim > i)
                return false;
            else
                last = max(last + 1, i - lim);
        return true;
    }

   public:
    int minLevel(vector<int> _heights) {
        heights = _heights;
        if (check(0)) return 0;
        int l = 0, r = 1e9;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            check(mid) ? r = mid : l = mid;
        }
        return r;
    }
} _;

#ifdef MACESUTED

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << _.minLevel(a) << endl;

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif