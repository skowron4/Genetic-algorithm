//
// Created by skowr on 15.01.2023.
//

#include "CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem() {
    i_itemCount = 0;
    i_bagSize = 0;
}

CKnapsackProblem::~CKnapsackProblem() {

}

int CKnapsackProblem::iCalculateFitness(vector<int> &genotype) {
    int result = 0;
    long size = 0;

    for (int i = 0; i < genotype.size(); ++i) {
        result += genotype[i] * vi_values[i];
        size += genotype[i] * vi_sizes[i];
    }

    if (size <= i_bagSize) return result;
    return -1;
}

bool CKnapsackProblem::bConfigurate(int itemsCount, int bagSize, vector<int> &values, vector<int> &sizes) {
    if (itemsCount < 2 || bagSize <= 0) return false;
    vi_values = values;
    vi_sizes = sizes;
    i_bagSize = bagSize;
    i_itemCount = itemsCount;

    return true;
}

bool CKnapsackProblem::bLoadData(const string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) return false;
    file >> i_itemCount;
    if (i_itemCount <= 0) return false;
    file >> i_bagSize;

    vi_sizes.resize(i_itemCount);
    vi_values.resize(i_itemCount);
    for (int i = 0; i < i_itemCount; i++) {
        file >> vi_values[i] >> vi_sizes[i];
    }
    file.close();

    return true;
}

int CKnapsackProblem::iGetIItemCount() const {
    return i_itemCount;
}
