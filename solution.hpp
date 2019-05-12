#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <bits/stdc++.h>

using namespace std;

extern vector<vector<double> > weights;
extern vector<vector<int> > reversed_triples;

class Solution {
    private:
        double score;
        int len;
        int tenor;
        int time;
        vector<int> v;
        vector<int> triple_qnt;
        vector<double> change_cost;
        vector<int> last_update;
    public:
        Solution(int n, int _tenor);

        double getScore();

        bool hasElem(int p);
        
        bool canAdd(int p);

        void localSearch();
};

#endif /* _SOLUTION_H_ */