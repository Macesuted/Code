#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 4005

stack<int> S;
bool ans[maxn];

int ask(int x, int y) {
    cout << "? " << x - 1 << ' ' << y - 1 << endl;
    char t;
    cin >> t;
    return t == 'Y';
}

void solve(void) {
    int a, b, x;
    cin >> a >> b;
    if (a <= b) return cout << "Impossible" << endl, void();
    for (int i = 1; i <= a + b; i++)
        if (S.empty())
            S.push(i);
        else if (ask(S.top(), i))
            S.push(i);
        else
            S.pop();
    x = S.top();
    for (int i = 1; i <= a + b; i++) ans[i] = ask(x, i);
    cout << "! ";
    for (int i = 1; i <= a + b; i++) cout << ans[i];
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
