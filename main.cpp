#include <iostream>
#include <chrono>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
int main() {
    srand(time(nullptr));
    CGeneticAlgorithm geneticAlgorithm;
    CKnapsackProblem knapsackProblem;
    knapsackProblem.bLoadData("../test1.txt");
    geneticAlgorithm.bConfigurate(knapsackProblem, 100, 0.6, 0.1);

    auto start = std::chrono::high_resolution_clock::now();
    geneticAlgorithm.vRunGA(3333);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout<<"czas: "<< duration.count()<<"\n";
    cout<< "Wynik: "<<geneticAlgorithm.getIBestResult() << "\n";
    cout << "Genotyp: ";
    for (int i = 0; i < geneticAlgorithm.getViBestGenotype().size(); ++i) {
        cout << geneticAlgorithm.getViBestGenotype()[i];
    }
}
