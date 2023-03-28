/**
 * @file 7681.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "committee.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

void rotate(int& x, int& y) { return tie(x, y) = make_pair(-y, x), void(); }

pii _(int id) { return id < 1e6 ? pii{id, 1e6} : pii{1e6, 2e6 - id}; }
long double qry(int x, int y, int O) {
    while (O--) rotate(x, y);
    return query(x, y);
}

void solve(int Q) {
    if (Q == 4) {
        int a = round(query(0, 1)), b = round(query(1, 0));
        long double c = (a > b ? query(1, -1) : query(-1, 1)), sqrt2 = sqrtl(2);
        int r = round((c - (a + b) / sqrt2) / (sqrt2 - 1));
        return report(a + r, b + r, r);
    }
    long double d[4] = {query(1, 0), query(0, 1), query(-1, 0), query(0, -1)}, mx = max({d[0], d[1], d[2], d[3]});
    int O = -1;
    for (int i = 0; i < 4; i++)
        if (d[i] != mx && d[(i + 1) % 4] == mx) O = i;
    int l = 0, r = 2e6;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (qry(_(mid).first, _(mid).second, O) == mx ? l : r) = mid;
    }
    pii func[5] = {_(r), _(r + 1), _(r + 2), _(r + 3), _(r + 4)};
    long double ans[5], ld[5];
    for (int i = 0; i < 5; i++)
        ans[i] = qry(func[i].first, func[i].second, O),
        ld[i] = sqrtl((int64_t)func[i].first * func[i].first + (int64_t)func[i].second * func[i].second);
    auto check = [&](int x, int y) {
        long double dis = sqrtl((int64_t)x * x + (int64_t)y * y);
        int r = round(dis - mx);
        if (fabsl(mx + r - dis) > 1e-11) return false;
        for (int i = 0; i < 5; i++) {
            long double a = func[i].second, b = -func[i].first, d = fabsl(a * x + b * y) / ld[i];
            if (fabsl(d - r - ans[i]) > 1e-11) return false;
        }
        while (O--) rotate(x, y);
        return report(x, y, r), true;
    };
    long double k = -(long double)_(l).first / _(l).second;
    int64_t lx = _(l).first, ly = _(l).second, rx = _(r).first, ry = _(r).second;
    for (int x = 1; x <= 1e5; x++) {
        int y = min(0, (int)round(x * k) + 50), yu = max((int)-1e5, (int)round(x * k) - 50);
        while (y >= yu && !(x * rx > ry * -y && x * lx <= ly * -y)) --y;
        while (y >= yu && x * rx > ry * -y && x * lx <= ly * -y) {
            if (check(x, y)) return;
            --y;
        }
    }
    return;
}