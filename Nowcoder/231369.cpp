#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    int n;
    cin >> n;
    int ans = 2;
    for (int i = 2; i <= n; i++)
        if (n / i != n / (i - 1)) ans++;
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}