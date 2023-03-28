#ifndef TEP6_CKNAPSACKPROBLEM_H
#define TEP6_CKNAPSACKPROBLEM_H

using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
class CKnapsackProblem {
public:
    CKnapsackProblem();
    ~CKnapsackProblem();

    int iCalculateFitness(vector<int> &genotype);
    bool bConfigurate(int itemsCount, int bagSize, vector<int> &values, vector<int> &sizes);
    bool bLoadData(const string fileName);
    int iGetIItemCount() const;
private:
    int i_itemCount;
    int i_bagSize;
    vector<int> vi_values;
    vector<int> vi_sizes;
};


#endif //TEP6_CKNAPSACKPROBLEM_H
