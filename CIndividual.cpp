//
// Created by skowr on 15.01.2023.
//

#include <random>
#include "CIndividual.h"

CIndividual::CIndividual() {
    i_fitness = -1;
}

CIndividual::CIndividual(vector<int> &genotype) {
    vi_genotype = genotype;
    i_fitness = -1;
}

CIndividual::CIndividual(const CIndividual &other) {
    i_fitness = other.i_fitness;
    vi_genotype = other.vi_genotype;
}

CIndividual::CIndividual(CIndividual &&other) {
    i_fitness = other.i_fitness;
    vi_genotype = std::move(other.vi_genotype);
}

CIndividual::~CIndividual() {

}

CIndividual &CIndividual::operator=(const CIndividual &other) {
    if (this != &other){
        vi_genotype = other.vi_genotype;
        i_fitness = other.i_fitness;
    }
    return *this;
}

void CIndividual::vCalculateFitness(CKnapsackProblem &problem) {
    i_fitness = problem.iCalculateFitness(vi_genotype);
}

bool CIndividual::bMutate(double mutationProbability) {
    for (int & i_gen : vi_genotype){
        if ((double) rand() / RAND_MAX < mutationProbability) {
            if (i_gen == 1) i_gen = 0;
            else i_gen = 1;
        }
    }
}

vector<CIndividual> CIndividual::vciCross3(CIndividual &other1, CIndividual &other2) {
    vector<int> genChild1;
    vector<int> genChild2;
    vector<int> parents;

    for (int i = 0; i < vi_genotype.size(); ++i) {
        parents = selectParents(other1, other2, i);
        genChild1.push_back(parents[0]);
        genChild2.push_back(parents[1]);
    }


    vector<CIndividual> result;
    result.push_back(CIndividual(genChild1));
    result.push_back(CIndividual(genChild2));
    result.push_back(CIndividual());
    return std::move(result);
}

vector<int> CIndividual::selectParents(CIndividual &other1, CIndividual &other2, int i){
    int index1 = 0;
    int index2 = 0;
    vector<int> result;

    index1 = rand() % 3;

    while (index1 == index2){
        index2 = rand() % 3;
    }

    if (index1 == 0 || index2 == 0) result.push_back(other1.vi_genotype[i]);
    if (index1 == 1 || index2 == 1) result.push_back(other2.vi_genotype[i]);
    if (index1 == 2 || index2 == 2) result.push_back(this->vi_genotype[i]);

    return std::move(result);
}

vector<CIndividual> CIndividual::vciCross(CIndividual &other) {
    vector<int> genChild1 = vi_genotype;
    vector<int> genChild2 = other.vi_genotype;

    int point = rand() / (vi_genotype.size());

    for (int i = point; i < vi_genotype.size(); ++i) {
        genChild1[i] = other.vi_genotype[i];
        genChild2[i] = vi_genotype[i];
    }
    vector<CIndividual> result;
    result.push_back(CIndividual(genChild1));
    result.push_back(CIndividual(genChild2));

    return std::move(result);
}

int CIndividual::iGetIFitness() const {
    return i_fitness;
}

const vector<int> &CIndividual::viGetIGenotype() const {
    return vi_genotype;
}

bool CIndividual::bConfigurate(int itemCount) {
    for (int i = 0; i < itemCount; ++i) {
        vi_genotype.push_back(rand() % 2);
    }
}
