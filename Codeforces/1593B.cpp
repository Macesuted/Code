/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005

void work(void) {
    string s;
    cin >> s;
    int answer = 0x3f3f3f3f;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] != '2' && s[i] != '7') continue;
        for (int j = i + 1; j < (int)s.size(); j++)
            if (s[j] == '5') answer = min(answer, (int)s.size() - i - 2);
    }
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] != '0' && s[i] != '5') continue;
        for (int j = i + 1; j < (int)s.size(); j++)
            if (s[j] == '0') answer = min(answer, (int)s.size() - i - 2);
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}