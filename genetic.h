#ifndef genetic_h
#define genetic_h
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

extern const int populationSize;
extern const double mutationRate;
extern const string targetIndividual;
extern const char possibleNucleotides[];


int fitness(const string &individual)
{
    int fitness = 0;
    for (size_t i = 0; i < individual.size(); i++)
    {
        if (individual[i] == targetIndividual[i])
        {
            fitness++;
        }
    }
    return fitness;
}

// crossover function that mimics real genetic recombination that occurs in nature
string crossover(const string &parent1, const string &parent2)
{
    string child = parent1;
    size_t crossoverPoint = rand() % parent1.size(); // THE RANDOM CROSSOVER POINT
    copy(parent2.begin() + crossoverPoint, parent2.end(), child.begin() + crossoverPoint);
    // takes the second parent at the crossover point, and copies the rest of the second parent into the child at the crossover point
    // so, the child is a combination of the two parents at the crossover point
    return child;
}

void mutate(string &individual)
{
    for (char &nucleotide : individual)
    {
        if (rand() / (RAND_MAX + 1.0) < mutationRate) // generates a random number between 0 and 1
        {
            nucleotide = possibleNucleotides[rand() % 4]; // sets the nucleotide to a random possiblity out of four (ACTG)
        }
    }
}

void naturalSelection(vector<string> &population)
{
    int deadIndividuals = populationSize / 10; // the lower 10% of the population will be deleted
    cout << endl
         << "Dead individuals: " << deadIndividuals << endl;

    population.erase(population.begin() + deadIndividuals, population.end());
    // fill the other 10% of the population with children from the top 10% of the population
    // this is to maintain the population size
    for (int i = 0; i < deadIndividuals; i += 2) // replace the dead individuals with children from more fit individuals, simulating natural selection
    {
        // simulating a constant population size, so two kids per two parents
        string parent1 = population[i];
        string parent2 = population[i + 1];
        string child1 = crossover(parent1, parent2);
        string child2 = crossover(parent2, parent1); // swap the parents for funsies, hopefully more random
        mutate(child1);
        mutate(child2);
        population.push_back(child1);
        population.push_back(child2);
    }
}

void geneFlow(vector<string> &population)
{
}

void geneticDrift(vector<string> &population)
{
}






#endif