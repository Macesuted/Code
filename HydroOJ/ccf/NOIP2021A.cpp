#include <bits/stdc++.h>
using namespace std;

bool mem1;

int readInt(void) {
    int x = 0, f = +1;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
void write(int v) {
    if (v < 0) putchar('-'), v = -v;
    if (v > 9) write(v / 10);
    putchar((v % 10) ^ 48);
    return;
}

#define maxv 10000005

bool vis[maxv];
int rig[maxv];

bool have7(int v) {
    while (v) {
        if (v % 10 == 7) return true;
        v /= 10;
    }
    return false;
}

int solve(void) {
    int x = readInt();
    if (vis[x]) return -1;
    return rig[x];
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("number.in", "r", stdin), freopen("number.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 1; i < maxv; i++) {
        if (vis[i] || !have7(i)) continue;
        for (int j = i; j < maxv; j += i) vis[j] = true;
    }
    for (int i = maxv - 1, last = -1; i; i--) {
        rig[i] = last;
        if (!vis[i]) last = i;
    }

    int _ = readInt();
    while (_--) write(solve()), putchar('\n');

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}