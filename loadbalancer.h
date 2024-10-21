#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include "webserver.h"
#include "request.h"

/**
 * @class LoadBalancer
 * @brief Manages web servers and distributes requests among them.
 *
 * The LoadBalancer class is responsible for managing multiple web servers,
 * adding incoming requests to a queue, and distributing those requests 
 * efficiently based on server availability.
 */
class LoadBalancer {
public:
    /**
     * @brief Construct a new LoadBalancer object.
     *
     * Initializes the LoadBalancer with a specified number of servers
     * and a queue size for incoming requests.
     *
     * @param server_count The number of web servers to manage.
     * @param queue_size The maximum size of the request queue.
     */
    LoadBalancer(int server_count, int queue_size);

    /**
     * @brief Add a request to the queue.
     *
     * This function adds a new request to the request queue for processing.
     *
     * @param request The request to be added to the queue.
     */
    void addRequest(const Request& request);

    /**
     * @brief Distribute requests to the available servers.
     *
     * This function iterates through the servers and assigns requests
     * from the queue to available servers for processing.
     */
    void distributeRequests();

    /**
     * @brief Adjust the number of active servers based on current load.
     *
     * This function monitors server availability and dynamically adjusts 
     * the number of active servers to optimize performance.
     */
    void adjustServers();

    /**
     * @brief Run the load balancer for a specified duration.
     *
     * This function manages the overall operation of the LoadBalancer,
     * processing requests and managing server load for the specified
     * amount of time.
     *
     * @param time_in_seconds The duration for which to run the load balancer.
     */
    void runFor(int time_in_seconds);

    /**
     * @brief Log the status of all web servers.
     *
     * This function prints the status of each web server, indicating
     * whether each server is available or busy processing requests.
     */
    void logServerStatus() const;
    /**
     * @brief Get the current size of the request queue.
     *
     * This function returns the number of remaining requests
     * in the request queue.
     *
     * @return The size of the request queue.
     */
    int getQueueSize() const;



private:
    std::vector<WebServer> servers;  ///< Collection of web servers managed by the LoadBalancer.
    std::queue<Request> requestqueue; ///< Queue holding incoming requests for processing.
};

#endif
