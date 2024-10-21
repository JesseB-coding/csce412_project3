#include "loadbalancer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

/**
 * @brief Main function that sets up the load balancer and runs it.
 *
 * The function initializes the LoadBalancer with user-specified
 * parameters, logs the initial and final queue sizes, and simulates
 * 10 servers running for a specified duration (e.g., 10000 clock cycles).
 */
int main() {
    int num_of_servers = 0;
    int time = 0;
    int queue_size = 0;

    cout << "Type how many servers you want: ";
    cin >> num_of_servers;
    cout << "How long would you want to run the load balancer?: ";
    cin >> time;
    cout << "Enter the initial queue size: ";
    cin >> queue_size;

    // Initialize LoadBalancer with user input
    LoadBalancer lb(num_of_servers, queue_size);

    // Create an output file to log the results
    ofstream logFile("server_log.txt");

    if (logFile.is_open()) {
        // Log the initial queue size
        logFile << "Starting queue size: " << lb.getQueueSize() << endl;

        // Run the load balancer for the specified time
        lb.runFor(time);

        // Log the final queue size after the load balancer finishes running
        logFile << "Ending queue size: " << lb.getQueueSize() << endl;

        // Assuming task times are between 1 and 500 milliseconds in the simulation
        logFile << "Task time range: 1-500 milliseconds." << endl;

        logFile.close();
        cout << "Log saved to server_log.txt" << endl;
    } else {
        cerr << "Unable to open log file!" << endl;
    }

    return 0;  ///< Return 0 upon successful execution
}
