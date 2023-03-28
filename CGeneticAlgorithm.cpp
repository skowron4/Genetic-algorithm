//
// Created by skowr on 15.01.2023.
//

#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm() {
    i_sizePopulation = 0;
    d_crossingProbability = 0;
    d_mutationProbability = 0;
    i_bestResult = 0;
}

CGeneticAlgorithm::~CGeneticAlgorithm() {

}

bool CGeneticAlgorithm::bConfigurate(CKnapsackProblem &knapsackProblem, int sizePop, double crossProb, double mutProb) {
    if (sizePop < 2) return false;
    ck_knapsackProblem = knapsackProblem;
    i_sizePopulation = sizePop;
    d_mutationProbability = mutProb;
    d_crossingProbability = crossProb;
    return true;
}

void CGeneticAlgorithm::vRunGA(int maxIter) {
    vInitializatePop();
    for (int i = 0; i < maxIter; ++i) {
        for (int j = 0; j < i_sizePopulation; j++) {
            vci_population[j].vCalculateFitness(ck_knapsackProblem);
        }
        vSelect();
        vCross();
        vMutation();
    }
}

void CGeneticAlgorithm::vInitializatePop() {
    vci_population.resize(i_sizePopulation);

    for (int i = 0; i < i_sizePopulation; ++i) {
        vci_population[i].bConfigurate(ck_knapsackProblem.iGetIItemCount());
    }
}

void CGeneticAlgorithm::vSelect() {
    for (int i = 0; i < vci_population.size(); ++i) {
        if (vci_population[i].iGetIFitness() == -1) vci_population[i].vCalculateFitness(ck_knapsackProblem);
        if (vci_population[i].iGetIFitness() > i_bestResult){
            i_bestResult = vci_population[i].iGetIFitness();
            vi_bestGenotype = vci_population[i].viGetIGenotype();
        }
    }
}

void CGeneticAlgorithm::vCross3() {
    vector<CIndividual> newPop;
    newPop.reserve(i_sizePopulation);
    CIndividual parent1;
    CIndividual parent2;
    CIndividual parent3;
    int index = 0;
    int index1 = 0;

    for (int i = 0; i < i_sizePopulation; i += 2) {
        parent1 = vci_population[iSelectParentIndex()];
        parent2 = vci_population[iSelectParentIndex()];
        parent3 = vci_population[iSelectParentIndex()];
        vector<CIndividual> children;

        if ((double) rand() / RAND_MAX < d_crossingProbability){
            children = parent1.vciCross3(parent2, parent3);
            newPop.push_back(children[0]);
            if (newPop.size() < i_sizePopulation) newPop.push_back(children[1]);
        } else{
            index = rand() % 3;
            while (index == index1){
                index1 = rand() % 3;
            }
            push(index, parent1, parent2, parent3, newPop);
            push(index1, parent1, parent2, parent3, newPop);

        }
    }

    vci_population = std::move(newPop);
//    cout <<"--------------------------------------------\n";
}

void CGeneticAlgorithm::push(int i, CIndividual &p1, CIndividual &p2, CIndividual &p3, vector<CIndividual> &newPop){
    if (i == 0) newPop.push_back(p1);
    if (i == 1) newPop.push_back(p2);
    else newPop.push_back(p3);
}

void CGeneticAlgorithm::vCross() {
    vector<CIndividual> newPop;
    newPop.reserve(i_sizePopulation);
    CIndividual parent1;
    CIndividual parent2;

    for (int i = 0; i < i_sizePopulation; i += 2) {
        parent1 = vci_population[iSelectParentIndex()];
        parent2 = vci_population[iSelectParentIndex()];
        vector<CIndividual> children;

        if ((double) rand() / RAND_MAX < d_crossingProbability){
            children = parent1.vciCross(parent2);
            newPop.push_back(children[0]);
            if(newPop.size() < i_sizePopulation) newPop.push_back(children[1]);
        } else {
            newPop.push_back(parent1);
            if(newPop.size() < i_sizePopulation) newPop.push_back(parent2);
        }
    }

    vci_population = std::move(newPop);
}

void CGeneticAlgorithm::vMutation() {
    for (int i = 0; i < vci_population.size(); ++i) {
        vci_population[i].bMutate(d_mutationProbability);
        vci_population[i].vCalculateFitness(ck_knapsackProblem);
    }
}

int CGeneticAlgorithm::iSelectParentIndex() {

    int index1 = rand() % (i_sizePopulation);
    int index2 = rand() % (i_sizePopulation);

    if (vci_population[index1].iGetIFitness() > vci_population[index2].iGetIFitness())
        return index1;
    else
        return index2;
}

int CGeneticAlgorithm::getIBestResult() const {
    return i_bestResult;
}

const vector<int> &CGeneticAlgorithm::getViBestGenotype() const {
    return vi_bestGenotype;
}
