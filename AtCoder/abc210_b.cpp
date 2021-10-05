/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

string str;

signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n >> str;
    str = ' ' + str;
    for (register int i = 1; i <= n; i++)
        if (str[i] == '1') {
            if (i & 1)
                cout << "Takahashi" << endl;
            else
                cout << "Aoki" << endl;
            break;
        }
    return 0;
}