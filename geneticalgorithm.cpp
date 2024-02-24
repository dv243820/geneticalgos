//
// A little project on genetic algorithms I'm working on
// The history of life is really cool to me so just messing around and seeing how it goes
//

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "genetic.h"
using namespace std;

const char possibleNucleotides[] = {'A', 'C', 'G', 'T'};                                  // for adenine, cytosine, guanine, and thymine, the four nucleotides that make up DNA of ALL LIVING THINGS ON EARTH
const int populationSize = 250;                                                     // number of individuals in the population
const double mutationRate = 0.001;                                                  // the rate of mutation
const string targetIndividual = "ACGTACGTACGTACGTACGTACGTACGTACGT"; // the target sequence we are trying to reach

// fitness function -- takes a string (indiviudal) and returns the number of matching nucleotides

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    // set up the population and randomize the individuals "genes"
    vector<string> population(populationSize);
    for (string &individual : population)
    {
        for (size_t i = 0; i < targetIndividual.size(); i++)
        {

            individual += possibleNucleotides[rand() % 4]; // sets the bit to a 0, 1, 2, or 3 to represent the ACTG sequence of genes
        }
    }

    int generation = 0; // we're tracking the number of generations it takes

    while (true)
    {
        // sort the population by fitness
        sort(population.begin(), population.end(), [](const string &a, const string &b)
             { return fitness(a) > fitness(b); });
        // natural selection occurs on the population
        // naturalSelection(population);

        sort(population.begin(), population.end(), [](const string &a, const string &b)
             { return fitness(a) > fitness(b); });
        // Show the most fit individual in the current generation
        cout << "Generation " << generation << ": " << population[0] << " " << fitness(population[0]) << endl;

        // check the target to see if we can break
        if ((population[0] == targetIndividual))
        {
            cout << "Target individual reached" << endl;
            cout << "Generation " << generation << ": " << population[0] << " " << fitness(population[0]) << endl;
            break;
        }

        // individual not reached, time to simulate the next generation
        vector<string> newPopulation(populationSize);

        for (int i = 0; i < populationSize; i += 2) // iterate by two, for parents
        {
            // simulating a constant population size, so two kids per two parents
            string parent1 = population[i];
            string parent2 = population[i + 1];
            string child1 = crossover(parent1, parent2);
            string child2 = crossover(parent2, parent1); // swap the parents for funsies, hopefully more random
            mutate(child1);
            mutate(child2);
            newPopulation[i] = child1;
            newPopulation[i + 1] = child2;
        }
        population = move(newPopulation); // move for efficiency
        generation++;
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << "milliseconds" << endl;

    return 0;
}
