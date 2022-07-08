/**
 * @file 24.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 5005
#define maxm 1000005

typedef pair<int, int> pii;

int a[maxn], lef[maxn], rig[maxn], disx[maxn], disy[maxn], id[maxm];

void findLocation(int n, int xp, int loc[], int typ[]) {
    int x = 0;
    id[loc[x] = xp] = typ[x] = 1;
    if (n == 1) return;
    for (int i = 1; i < n; i++) disx[i] = getDistance(x, i), a[i] = i;
    sort(a + 1, a + n, [&](int p1, int p2) { return disx[p1] < disx[p2]; });
    int y = a[1];
    id[loc[y] = loc[x] + disx[y]] = typ[y] = 2;
    for (int i = 0; i < n; i++)
        if (a[i] != y) disy[a[i]] = getDistance(y, a[i]);
    int lcnt = 0, rcnt = 0;
    for (int i = 2; i < n; i++)
        if (disx[y] + disy[a[i]] == disx[a[i]])
            if (disy[a[i]] < disx[y])
                id[loc[a[i]] = loc[y] - disy[a[i]]] = typ[a[i]] = 1;
            else
                lef[lcnt++] = a[i];
        else
            rig[rcnt++] = a[i];
    for (int i = 0, c = x; i < lcnt; i++) {
        int d = getDistance(c, lef[i]), len = (disy[c] + d - disy[lef[i]]) / 2;
        if (id[loc[c] + len] == 1)
            id[loc[lef[i]] = loc[c] + d] = typ[lef[i]] = 2;
        else
            id[loc[lef[i]] = loc[y] - disy[lef[i]]] = typ[lef[i]] = 1, c = lef[i];
    }
    for (int i = 0, c = y; i < rcnt; i++) {
        int d = getDistance(c, rig[i]), len = (disx[c] + d - disx[rig[i]]) / 2;
        if (id[loc[c] - len] == 2)
            id[loc[rig[i]] = loc[c] - d] = typ[rig[i]] = 1;
        else
            id[loc[rig[i]] = loc[x] + disx[rig[i]]] = typ[rig[i]] = 2, c = rig[i];
    }
    return;
}
