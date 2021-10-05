/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

void work(void) {
    int n;
    string s;
    cin >> n >> s;
    int answer = 0;
    for (register int i = 0; i < s.size(); i++) {
        if (s[i] == '0') continue;
        answer += s[i] - '0';
        if (i != s.size() - 1) answer++;
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}