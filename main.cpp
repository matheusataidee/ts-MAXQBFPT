#include <bits/stdc++.h>

#include "solution.hpp"

using namespace std;

int n;
vector<vector<double> > weights;
vector<vector<int> > triples;
vector<vector<int> > reversed_triples;

int lFunction(int u, int pi_1, int pi_2) {
    return 1 + (pi_1 * u + pi_2) % n;
}

void mountTriples() {
    for (int i = 0; i < n; i++) {
        triples[i][0] = i + 1;

        int g = lFunction(i, 131, 1031);
        if (g != triples[i][0]) {
            triples[i][1] = g;
        } else {
            triples[i][1] = 1 + (g % n);
        }

        int h = lFunction(i, 193, 1093);
        int x = 1 + (h % n);
        if (h != triples[i][0] && h != triples[i][1]) {
            triples[i][2] = h;
        } else if (x != triples[i][0] && x != triples[i][1]) {
            triples[i][2] = x;
        } else {
            triples[i][2] = 1 + (h + 1) % n;
        }
        sort(triples[i].begin(), triples[i].end());
        for (int j = 0; j < 3; j++) {
            triples[i][j]--;
            reversed_triples[triples[i][j]].push_back(i);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "No instance provided" << endl;
        return -1;
    }
    ifstream fin(argv[1]);
    fin >> n;
    weights = vector<vector<double> >(n, vector<double>(n, 0.0 ));
    triples = vector<vector<int> >(n, vector<int>(3, 0));
    reversed_triples = vector<vector<int> >(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            fin >> weights[i][j];
            if (j > i) {
                weights[j][i] = 0;
            }
        }
    }
    fin.close();
    mountTriples();
    Solution solution(n, 10);
    Solution best_solution(n, 10);
    for (int i = 0; i < 5000; i++) {
        solution.localSearch();
        if (solution.getScore() > best_solution.getScore()) {
            best_solution = solution;
        }
    }
    bool invalid = false;
    for (int i = 0; i < n; i++) {
        if (best_solution.hasElem(triples[i][0]) && best_solution.hasElem(triples[i][1]) && best_solution.hasElem(triples[i][2])) {
            cout << "INVALID" << endl;
            invalid = true;
        }
    }
    if (invalid == false) {
        cout << "Valid solution confirmed" << endl;
    }

    double partial = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (best_solution.hasElem(i) && best_solution.hasElem(j)) {
                partial += weights[i][j];
            }
        }
    }
    cout << "partial = " << partial << endl;
    cout << "best_solution score = " <<  best_solution.getScore() << endl;
    return 0;
}