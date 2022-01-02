/**
 * @file 1605D2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 10005

bool ask(int x, int y, int z) {
    cout << "? " << x << ' ' << y << ' ' << z << endl;
    int t;
    cin >> t;
    return t;
}

int a[maxn], v[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i += 3) a[i] = ask(i, i + 1, i + 2);
    int p0 = 0, p1 = 0;
    for (int i = 1; i <= n; i += 3)
        if (a[i] == 0 && !p0)
            p0 = i;
        else if (a[i] == 1 && !p1)
            p1 = i;

    bool b1 = ask(p0, p0 + 1, p1), b2 = ask(p0, p0 + 1, p1 + 1), b3 = ask(p0, p0 + 1, p1 + 2);
    if (b1 || b2 || b3) {
        v[p1] = b1, v[p1 + 1] = b2, v[p1 + 2] = b3;
        int o1 = 0;
        for (int i = p1; i < p1 + 3; i++)
            if (v[i] == 1) o1 = i;
        bool b4 = ask(o1, p0, p0 + 1), b5 = ask(o1, p0, p0 + 2);
        if (b4 && b5) tie(v[p0], v[p0 + 1], v[p0 + 2]) = make_tuple(1, 0, 0);
        if (!b4 && b5) tie(v[p0], v[p0 + 1], v[p0 + 2]) = make_tuple(0, 0, 1);
        if (b4 && !b5) tie(v[p0], v[p0 + 1], v[p0 + 2]) = make_tuple(0, 1, 0);
        if (!b4 && !b5) tie(v[p0], v[p0 + 1], v[p0 + 2]) = make_tuple(0, 0, 0);
    } else {
        v[p0] = v[p0 + 1] = 0;
        bool b4 = ask(p0, p1, p1 + 1), b5 = ask(p0, p1, p1 + 2);
        if (b4 && b5) tie(v[p1], v[p1 + 1], v[p1 + 2]) = make_tuple(1, 1, 1);
        if (!b4 && b5) tie(v[p1], v[p1 + 1], v[p1 + 2]) = make_tuple(1, 0, 1);
        if (b4 && !b5) tie(v[p1], v[p1 + 1], v[p1 + 2]) = make_tuple(1, 1, 0);
        if (!b4 && !b5) tie(v[p1], v[p1 + 1], v[p1 + 2]) = make_tuple(0, 1, 1);
        int o1 = 0;
        for (int i = p1; i < p1 + 3; i++)
            if (v[i] == 1) o1 = i;
        v[p0 + 2] = ask(p0 + 1, p0 + 2, o1);
    }
    int o0 = 0, o1 = 0;
    for (int i = p0; i < p0 + 3; i++)
        if (v[i] == 0)
            o0 = i;
        else
            o1 = i;
    for (int i = p1; i < p1 + 3; i++)
        if (v[i] == 0)
            o0 = i;
        else
            o1 = i;
    for (int i = 1; i <= n; i += 3) {
        if (i == p0 || i == p1) continue;
        if (a[i] == 0) {
            bool b4 = ask(o1, i, i + 1), b5 = ask(o1, i, i + 2);
            if (b4 && b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(1, 0, 0);
            if (!b4 && b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(0, 0, 1);
            if (b4 && !b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(0, 1, 0);
            if (!b4 && !b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(0, 0, 0);
        } else {
            bool b4 = ask(o0, i, i + 1), b5 = ask(o0, i, i + 2);
            if (b4 && b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(1, 1, 1);
            if (!b4 && b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(1, 0, 1);
            if (b4 && !b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(1, 1, 0);
            if (!b4 && !b5) tie(v[i], v[i + 1], v[i + 2]) = make_tuple(0, 1, 1);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += (v[i] == 0);
    cout << "! " << cnt;
    for (int i = 1; i <= n; i++)
        if (v[i] == 0) cout << ' ' << i;
    cout << endl;
    return;
}

bool mem2;

int main() {
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
