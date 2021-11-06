#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 105
#define maxv 20005

typedef pair<int, int> pii;

int a[maxn];
bool notPrime[maxv];
vector<int> prime;

void init(void) {
    notPrime[1] = true;
    for (int i = 2; i < maxv; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j : prime) {
            if (i * j >= maxv) break;
            notPrime[i * j] = true;
            if (i % j == 0) break;
        }
    }
    return;
}

void solve(void) {
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    if (notPrime[sum]) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) cout << i << ' ';
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++)
        if (notPrime[sum - a[i]]) {
            cout << n - 1 << endl;
            for (int j = 1; j <= n; j++)
                if (i != j) cout << j << ' ';
            cout << endl;
            return;
        }
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    init();

    int _ = 1;
    cin >> _;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}