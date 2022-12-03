/**
 * @file 235.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

vector<pii> a;

vector<int> find_subset(int l, int r, vector<int> w) {
    int n = w.size();
    for (int i = 0; i < n; i++) a.emplace_back(w[i], i);
    sort(a.begin(), a.end());
    int64_t suml = 0, sumr = 0;
    for (int i = 1; i <= n; i++) {
        suml += a[i - 1].first, sumr += a[n - i].first;
        vector<int> ans;
        if (suml <= r && l <= sumr) {
            for (int j = i - 1, k = n - 1, sum = suml; ~j; j--) {
                while ((int64_t)sum + a[k].first - a[j].first > r) k--;
                ans.push_back(a[k].second), sum += a[k].first - a[j].first, k--;
            }
            return ans;
        }
    }
    return vector<int>{};
}
