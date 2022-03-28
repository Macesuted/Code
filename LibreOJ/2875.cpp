/**
 * @file 2875.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ramen.h"
//
#include <bits/stdc++.h>

using namespace std;

#define maxn 405

int id[maxn];

void Ramen(int n) {
    for (int i = 0; i < n; i++) id[i] = i;
    if (n & 1) id[n] = n - 1, n++;
    for (int i = 0; i < n; i += 2)
        if (id[i] != id[i + 1] && Compare(id[i], id[i + 1]) == -1) swap(id[i], id[i + 1]);
    int maxp = id[0], minp = id[1];
    for (int i = 2; i < n; i += 2)
        if (Compare(id[i], maxp) == 1) maxp = id[i];
    for (int i = 3; i < n; i += 2)
        if (Compare(id[i], minp) == -1) minp = id[i];
    Answer(minp, maxp);
    return;
}