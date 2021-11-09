#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

map<int, int> S;
int n, k;

int dfs(int p) {
    if (p <= k) return 1;
    if (S.find(p) != S.end()) return S[p];
    int mid = p >> 1;
    return S[p] = 1 + dfs(mid) + dfs(p - mid);
}

void solve(void) {
    cin >> n >> k;
    cout << dfs(n) << endl;
    S.clear();
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