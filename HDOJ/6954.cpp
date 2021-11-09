#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 10000005
#define mod 998244353

vector<int> prime;
bool vis[maxn];

void init(void) {
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) prime.push_back(i);
        for (auto j : prime) {
            if (i * j >= maxn) break;
            vis[i * j] = true;
            if (i % j == 0) break;
        }
    }
    return;
}
void solve(void) {
    long long n, ans = 0;
    cin >> n;
    for (int i = 3; i <= n; i++) ans += i * (1 + !vis[i]);
    cout << ans << endl;
    return;
}

bool mem2;

signed main() {
    ios::sync_with_stdio(false);
    init();
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}