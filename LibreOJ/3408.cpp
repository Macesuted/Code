/**
 * @file 3408.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "lancllords.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 150005

typedef pair<int, int> pii;

int x_ = 0, y_ = 0;
bool comp(int x, int y) {
    while (x_ < x) inc_p(), x_++;
    while (x_ > x) dec_p(), x_--;
    while (y_ < y) inc_q(), y_++;
    while (y_ > y) dec_q(), y_--;
    return cmp();
}

int n, pos[maxn];

vector<int> merge(vector<int> a, vector<int> b, int length) {
    if (a.size() == 1 && b.size() == 1) {
        if (!comp(a[0], b[0])) swap(a, b);
        return vector<int>{a[0], b[0]};
    }
    if (a.size() < b.size()) swap(a, b);
    vector<int> c;
    for (int i = 0; i < (int)a.size(); i += 2) c.push_back(a[i]);
    b = merge(b, c, length);
    for (int i = 0; i < (int)b.size(); i++) pos[b[i]] = i;
    vector<pii> ques;
    for (int i = 1; i < (int)a.size(); i += 2) {
        int l = pos[a[i - 1]], r = (i + 1 == (int)a.size() ? (int)b.size() : pos[a[i + 1]]);
        pos[a[i]] = r;
        for (int j = l + 1; j < r; j++) ques.emplace_back(a[i], b[j]);
    }
    int len = length / sqrt(0.38 * ques.size());
    sort(ques.begin(), ques.end(), [=](const pii& a, const pii& b) {
        return get<0>(a) / len == get<0>(b) / len ? (((get<0>(a) / len) & 1) ? get<1>(a) > get<1>(b) : get<1>(a) < get<1>(b))
                                                  : (get<0>(a) < get<0>(b));
    });
    for (auto& i : ques)
        if (comp(get<0>(i), get<1>(i))) pos[get<0>(i)] = min(pos[get<0>(i)], pos[get<1>(i)]);
    vector<int> ans;
    for (int i = 0; i < (int)b.size() && b[i] != a.front(); i++) ans.push_back(b[i]);
    for (int i = 1; i < (int)a.size(); i += 2) {
        int l = pos[a[i - 1]], r = (i + 1 == (int)a.size() ? (int)b.size() : pos[a[i + 1]]);
        for (int j = l; j < pos[a[i]]; j++) ans.push_back(b[j]);
        ans.push_back(a[i]);
        for (int j = pos[a[i]]; j < r; j++) ans.push_back(b[j]);
    }
    if ((int)a.size() & 1)
        for (int i = pos[a.back()]; i < (int)b.size(); i++) ans.push_back(b[i]);
    return ans;
}

void solve(vector<int>& a) {
    if (a.size() <= 1) return;
    vector<int> b;
    while (a.size() > b.size()) b.push_back(a.back()), a.pop_back();
    solve(a), solve(b);
    a = merge(a, b, (int)a.size());
    return void();
}

vector<int> answer(int n_) {
    n = n_;
    vector<int> a;
    for (int i = 0; i < n; i++) a.push_back(i);
    solve(a);
    vector<int> ans;
    ans.resize(n);
    for (int i = 0; i < n; i++) ans[a[i]] = i;
    return ans;
}
