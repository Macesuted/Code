/**
 * @file 2764.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, I = 0, OI = 0, IOI = 0, JOI = 0;
    string s;
    cin >> n >> s;
    for (int i = n - 1; ~i; i--) {
        if (s[i] == 'O')
            OI += (OI < I);
        else if (s[i] == 'I')
            IOI += (IOI < OI && IOI * 2 < I), I++;
        else if (OI)
            IOI -= (OI == IOI || IOI * 2 == I), OI--, I--, JOI++;
    }
    cout << IOI + JOI << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}