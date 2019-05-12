#include "solution.hpp"

Solution::Solution(int n, int _tenor) {
    len = n;
    tenor = _tenor;
    score = 0.0;
    time = 0;
    v = vector<int>(n, 0);
    triple_qnt = vector<int>(n, 0);
    change_cost = vector<double>(n, 0.0);
    last_update = vector<int>(n, -tenor - 1);
    for (int i = 0; i < n; i++) {
        change_cost[i] = weights[i][i];
    }
}

double Solution::getScore() {
    return score;
}

bool Solution::hasElem(int p) {
    if (v[p] == 1) return true;
    return false;
}

bool Solution::canAdd(int p) {
    for (int i = 0; i < reversed_triples[p].size(); i++) {
        int val = reversed_triples[p][i];
        if (triple_qnt[val] == 2) return false;
    }
    return true;
}

void Solution::localSearch() {
    double best_update = -999999999;
    int id = -1;
    for (int i = 0; i < len; i++) {
        if (last_update[i] + tenor > time) continue;
        if (v[i]) {
            if (-change_cost[i] > best_update) {
                best_update = -change_cost[i];
                id = i;
            }
        } else {
            if (!canAdd(i)) continue;
            if (change_cost[i] > best_update) {
                best_update = change_cost[i];
                id = i;
            }
        }
    }
    time++;
    if (id == -1) return;
    last_update[id] = time;
    if (v[id]) {
        v[id] = 0;
        score -= change_cost[id];
        for (int i = 0; i < reversed_triples[id].size(); i++) {
            int val = reversed_triples[id][i];
            triple_qnt[val]--;
        }
        for (int i = 0; i < len; i++) {
            if (i == id) continue;
            change_cost[i] -= (weights[i][id] + weights[id][i]);
        }
    } else {
        v[id] = 1;
        score += change_cost[id];
        for (int i = 0; i < reversed_triples[id].size(); i++) {
            int val = reversed_triples[id][i];
            triple_qnt[val]++;
        }
        for (int i = 0; i < len; i++) {
            if (i == id) continue;
            change_cost[i] += (weights[i][id] + weights[id][i]);
        }
    }
}