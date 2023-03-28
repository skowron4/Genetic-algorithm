#ifndef TEP6_CGENETICALGORITHM_H
#define TEP6_CGENETICALGORITHM_H


#include <random>
#include "CIndividual.h"
using namespace std;
class CGeneticAlgorithm {
public:
    CGeneticAlgorithm();
    ~CGeneticAlgorithm();

    bool bConfigurate(CKnapsackProblem &knapsackProblem, int sizePop, double crossProb, double mutProb);
    void vRunGA(int maxIter);
    void vInitializatePop();
    int getIBestResult() const;
    const vector<int> &getViBestGenotype() const;

private:
    int i_sizePopulation;
    double d_crossingProbability;
    double d_mutationProbability;
    int i_bestResult;

//    mt19937 mt_random;

    CKnapsackProblem ck_knapsackProblem;
    vector<CIndividual> vci_population;
    vector<int> vi_bestGenotype;

    void vSelect();
    void vCross3();
    void push(int i, CIndividual &p1, CIndividual &p2, CIndividual &p3, vector<CIndividual> &newPop);
    void vCross();
    void vMutation();

    int iSelectParentIndex();
};


#endif //TEP6_CGENETICALGORITHM_H
