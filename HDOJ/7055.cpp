#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 100005
#define mod 998244353

string s;

vector<int> pos[26];

void solve(void) {
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    for (int i = 1; i <= n; i++) pos[s[i] - 'a'].push_back(i);
    long long answer = 0;
    for (int t = 0; t < 26; t++) {
        long long sum = 0;
        for (auto i : pos[t]) sum += n - i + 1;
        for (auto i : pos[t])
            sum -= n - i + 1, answer = (answer + i * sum * 2 + i * (n - i + 1)) % mod;
        pos[t].clear();
    }
    cout << answer << endl;
    return;
}

bool mem2;

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}