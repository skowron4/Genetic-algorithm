#ifndef TEP6_CINDIVIDUAL_H
#define TEP6_CINDIVIDUAL_H

#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"
using namespace std;
class CIndividual {
public:
    CIndividual();
    CIndividual(vector<int> &genotype);
    CIndividual(const CIndividual &other);
    CIndividual(CIndividual &&other);
    ~CIndividual();

    CIndividual &operator=(const CIndividual &other);

    bool bConfigurate(int itemCount);
    int iGetIFitness() const;
    const vector<int> &viGetIGenotype() const;
    void vCalculateFitness(CKnapsackProblem &problem);
    bool bMutate(double mutationProbability);
    vector<CIndividual> vciCross(CIndividual &other);
    vector<CIndividual> vciCross3(CIndividual &other1, CIndividual &other2);
    vector<int> selectParents(CIndividual &other1, CIndividual &other2, int i);
private:
    vector<int> vi_genotype;
    int i_fitness;
};


#endif //TEP6_CINDIVIDUAL_H
