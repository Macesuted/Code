/**
 * @file 1605B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

const int prime[22] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};

void solve(void) {
    int n;
    cin >> n;
    n--;
    for (int i = 0; i < 22; i++)
        if (n % prime[i] != 0) {
            cout << prime[i] << ' ' << n - prime[i] << ' ' << 1 << endl;
            return;
        }
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
