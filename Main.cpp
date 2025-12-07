#include "LinkedQueue.hpp" // Included for class definition
#include "ArrayQueue.hpp"  // Included for class definition
#include "QueueFactory.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>

using namespace std;

// Function to run a single simulation scenario
void runSimulation(const string& title, Queue<int>* q, int max_iterations, double dequeue_prob, double enqueue_threshold) {
    cout << "------------------------------------------\n";
    cout << "Simulation: " << title << endl;
    cout << "Max Iterations: " << max_iterations << endl;
    
    // Seed the random generator
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-1.0, enqueue_threshold); // Generates [-1.0, threshold]

    int servedCount = 0;
    int arrivedCount = 0;
    int turnedAwayCount = 0;

    for (int i = 0; i < max_iterations; ++i) {
        double randomNumber = distribution(generator);

        // Dequeue condition: number is negative
        if (randomNumber < 0) {
            if (!q->isEmpty()) {
                q->dequeue();
                servedCount++;
            }
        }
        // Enqueue condition: number is 0 or positive
        else {
            try {
                // The actual value stored is not important, use '1'
                q->enqueue(1);
                arrivedCount++;
            } catch (const string& e) {
                // Catch the 'queue is full' exception from ArrayQueue
                if (e.find("full") != string::npos) {
                    turnedAwayCount++;
                }
            }
        }
    }

    cout << "Final Queue Size: " << q->getLength() << endl;
    cout << "Total Arrivals (attempted): " << arrivedCount + turnedAwayCount << endl;
    cout << "Total Served: " << servedCount << endl;
    cout << "Total Turned Away (Only Sim 1): " << turnedAwayCount << endl;
    cout << "------------------------------------------\n";
}


int main() {
    // Ensure random numbers are different on each run
    srand(time(0)); 

    // --- Simulation Example 1: Ticket Counter (Fixed Size) ---
    const int MAX_CUSTOMERS_1 = 10;
    // Use Factory with size > 0 to get ArrayQueue
    Queue<int>* queue1 = QueueFactory<int>::GetQueue(MAX_CUSTOMERS_1);
    
    // Dequeue if [-1, 0), Enqueue if [0, 1]. Threshold = 1 (equal probability).
    // The generator is [-1, 1], so dequeue prob = 50%
    runSimulation("Ticket Counter (Array-Based, Fixed Size=10)", 
                  queue1, 
                  100, 
                  1.0, 
                  1.0);
    
    delete queue1;


    // --- Simulation Example 2: Bank Service Line (Dynamic Size) ---
    // Use Factory with size = 0 (default) to get LinkedQueue
    Queue<int>* queue2 = QueueFactory<int>::GetQueue(); 
    
    // Dequeue if [-1, 0), Enqueue if [0, 2]. Threshold = 2 (Enqueue is 3x more likely).
    // The generator is [-1, 2], so dequeue prob = 33% (1/3rd of the range).
    runSimulation("Bank Service Line (Linked List-Based, Dynamic Size)", 
                  queue2, 
                  100, 
                  1.0, 
                  2.0);

    delete queue2;

    return 0;
}