/**
 * @file 1634D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

int ask(int x, int y, int z) {
    cout << "? " << x << ' ' << y << ' ' << z << endl;
    int t;
    cin >> t;
    return t;
}

pair<int, int> solve(int p1, int p2, int p3, int p4) {
    int n123 = ask(p1, p2, p3), n124 = ask(p1, p2, p4), n134 = ask(p1, p3, p4), n234 = ask(p2, p3, p4);
    int nm = max({n123, n124, n134, n234});
    if (nm == n123) {
        if (nm == n124)
            return MP(p1, p2);
        else if (nm == n134)
            return MP(p1, p3);
        else if (nm == n234)
            return MP(p2, p3);
    } else if (nm == n124) {
        if (nm == n134)
            return MP(p1, p4);
        else if (nm == n234)
            return MP(p2, p4);
    } else if (nm == n134) {
        if (nm == n234) return MP(p3, p4);
    }
    return MP(0, 0);
}

void solve(void) {
    int n;
    cin >> n;
    int p1 = 1, p2 = 2;
    for (int i = 3; i < n; i += 2) tie(p1, p2) = solve(p1, p2, i, i + 1);
    if (n & 1) {
        int p3 = 1;
        while (p1 == p3 || p2 == p3) p3++;
        tie(p1, p2) = solve(p1, p2, p3, n);
    }
    cout << "! " << p1 << ' ' << p2 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
