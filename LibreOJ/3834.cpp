/**
 * @file 3834.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "insects.h"
#include <bits/stdc++.h>
using namespace std;

int min_cardinality(int n) {
    mt19937 rnd(20080618);
    vector<int> S, T;
    for (int i = 0; i < n; i++) {
        move_inside(i);
        if (press_button() == 1)
            S.push_back(i);
        else
            T.push_back(i), move_outside(i);
    }
    int k = S.size();
    for (auto i : S) move_outside(i);
    S = T, T.clear();
    int l = 1, r = n / k + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        shuffle(S.begin(), S.end(), rnd);
        vector<int> Tu, Td;
        for (auto i : S) {
            if ((int)Td.size() == k * (mid - l)) {
                Tu.push_back(i);
                continue;
            }
            move_inside(i);
            if (press_button() <= mid - l)
                Td.push_back(i);
            else
                Tu.push_back(i), move_outside(i);
        }
        for (auto i : Td) move_outside(i);
        if ((int)Td.size() != k * (mid - l))
            r = l + (int)Td.size() / k + 1, S = Td;
        else
            l = mid, S = Tu;
    }
    return l;
}