#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 105

typedef pair<int, int> pii;

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cout << "?";
        for (int j = 1; j < n; j++) cout << ' ' << i;
        cout << ' ' << 1 << endl;
        int ret;
        cin >> ret;
        if (ret == 0) {
            a[n] = i - 1;
            break;
        }
        a[ret] = -i + 1;
    }
    for (int i = 2; i <= n; i++) {
        cout << "?";
        for (int j = 1; j < n; j++) cout << ' ' << 1;
        cout << ' ' << i << endl;
        int ret;
        cin >> ret;
        if (ret == 0) {
            a[n] = n + 2 - i;
            break;
        }
        a[ret] = +i - 1;
    }
    for (int i = 1; i < n; i++) a[i] += a[n];
    cout << "!";
    for (int i = 1; i <= n; i++) cout << ' ' << a[i];
    cout << endl;
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}