#include "loadbalancer.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/**
 * @brief Construct a new LoadBalancer object.
 *
 * Initializes a specified number of web servers and generates
 * initial requests to fill the request queue.
 *
 * @param server_count The number of web servers to create.
 * @param queue_size The number of initial requests to generate.
 */
LoadBalancer::LoadBalancer(int server_count, int queue_size) {
    // Initialize the specified number of servers
    for (int i = 0; i < server_count; ++i) {
        servers.emplace_back(i + 1);  // Create WebServer objects with unique IDs
    }

    // Generate initial requests and fill the request queue (servers * 100 requests)
    for (int i = 0; i < queue_size; ++i) {
        // Generate random request details (random IP addresses, processing time, job type)
        Request req("192.168.1.1", "10.0.0.5", rand() % 500 + 1, (rand() % 2 == 0) ? 'P' : 'S');
        requestqueue.push(req);  // Push the request to the queue
    }
}

/**
 * @brief Add a new request to the request queue.
 *
 * This function adds a request to the queue for processing.
 *
 * @param request The request to be added to the queue.
 */
void LoadBalancer::addRequest(const Request& request) {
    requestqueue.push(request);
}

/**
 * @brief Distribute requests to the available servers.
 *
 * This function iterates through all servers and assigns requests
 * from the queue to the servers that are available.
 */
void LoadBalancer::distributeRequests() {
    while (!requestqueue.empty()) {
        for (auto& server : servers) {
            if (server.isAvailable() && !requestqueue.empty()) {
                server.takeRequest(requestqueue.front());  // Assign the next request to the server
                requestqueue.pop();  // Remove the request from the queue after assignment
            }
        }
    }
}

/**
 * @brief Adjust the number of active servers based on current load.
 *
 * This function monitors the size of the request queue and adjusts
 * the number of active servers accordingly. It adds new servers 
 * if the queue is too large and removes idle servers if the queue 
 * is small.
 */
void LoadBalancer::adjustServers() {
    // Add new servers if the queue gets too large
    if (requestqueue.size() > servers.size() * 50) {  // Threshold: 50 requests per server
        WebServer newServer(servers.size() + 1);
        servers.push_back(newServer);
        std::cout << "Added a new WebServer. Total servers: " << servers.size() << std::endl;
    }

    // Remove idle servers if the queue is small
    if (requestqueue.size() < servers.size() * 10 && servers.size() > 1) {  // Threshold: less than 10 requests per server
        servers.pop_back();  // Remove the last server
        std::cout << "Removed an idle WebServer. Total servers: " << servers.size() << std::endl;
    }
}

/**
 * @brief Run the load balancer for a specified number of clock cycles.
 *
 * This function manages the overall operation of the LoadBalancer,
 * processing requests and managing server load for the specified
 * number of clock cycles.
 *
 * @param clock_cycles The number of clock cycles to run the load balancer.
 */
void LoadBalancer::runFor(int clock_cycles) {
    //auto start = std::chrono::high_resolution_clock::now();  // Record start time
    srand(time(nullptr));

    for (int cycle = 0; cycle < clock_cycles; ++cycle) {
        adjustServers();           // Adjust the number of active servers
        distributeRequests();      // Distribute requests to servers

        // Simulate random new requests being added to the queue
        if (rand() % 100 < 10) {  // 10% chance to add a new request each iteration
            Request newRequest("172.16.0.1", "192.168.0.2", rand() % 500 + 1, (rand() % 2 == 0) ? 'P' : 'S');
            addRequest(newRequest);
            std::cout << "New request added to the queue." << std::endl;
        }

        // Log server status every few cycles (e.g., every 100 cycles)
        if (cycle % 100 == 0) {
            logServerStatus();  // Log the status of all servers
        }

        // Introduce a small sleep to simulate time between request processing cycles
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Adjust sleep time if necessary
    }
}


/**
 * @brief Log the status of all web servers.
 *
 * This function prints the status of each web server, indicating
 * whether it is available or busy.
 */
void LoadBalancer::logServerStatus() const {
    std::cout << "Current server statuses:\n";
    for (const auto& server : servers) {
        std::cout << "WebServer " << server.getID() << (server.isAvailable() ? " is available." : " is busy.") << std::endl;
    }
}

/**
 * @brief Get the current size of the request queue.
 *
 * This function returns the number of remaining requests in the request queue,
 * allowing monitoring of how many tasks are still pending in the system.
 *
 * @return The size of the request queue as an integer.
 */
int LoadBalancer::getQueueSize() const {
    return requestqueue.size();
}

