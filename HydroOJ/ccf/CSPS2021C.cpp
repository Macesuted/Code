#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 500005

int a[maxn << 1], pos[maxn][2];
vector<char> answer[2];
int rec;

bool work(int l, int r, int tl, int tr) {
    rec = l;
    answer[0].clear(), answer[1].clear();
    while (l < tl || tr < r) {
        if (l + 1 < tl && a[l] == a[tl - 1])
            answer[0].push_back('L'), answer[1].push_back('L'), l++, tl--;
        else if (l < tl && tr < r && a[l] == a[tr + 1])
            answer[0].push_back('L'), answer[1].push_back('R'), l++, tr++;
        else if (r > tr && l < tl && a[r] == a[tl - 1])
            answer[0].push_back('R'), answer[1].push_back('L'), r--, tl--;
        else if (r - 1 > tr && a[r] == a[tr + 1])
            answer[0].push_back('R'), answer[1].push_back('R'), r--, tr++;
        else
            return false;
    }
    return true;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) pos[i][0] = pos[i][1] = 0;
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        if (pos[a[i]][0])
            pos[a[i]][1] = i;
        else
            pos[a[i]][0] = i;
    }
    if (work(2, 2 * n, pos[a[1]][1], pos[a[1]][1]) || work(1, 2 * n - 1, pos[a[2 * n]][0], pos[a[2 * n]][0])) {
        cout << (rec == 2 ? 'L' : 'R');
        for (auto i = answer[0].begin(); i != answer[0].end(); i++) cout << *i;
        for (auto i = answer[1].rbegin(); i != answer[1].rend(); i++) cout << *i;
        cout << 'L' << endl;
    } else
        cout << "-1" << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("palin.in", "r", stdin), freopen("palin.out", "w", stdout);
#endif
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    clock_t tim1 = clock();
    ios::sync_with_stdio(false);

    int _;
    cin >> _;
    while (_--) solve();

    clock_t tim2 = clock();
    cerr << "Time: " << (tim2 - tim1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}