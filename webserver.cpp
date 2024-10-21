#include "webserver.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/**
 * @brief Construct a new WebServer object.
 *
 * Initializes the web server with a unique identifier and sets its
 * availability status to true.
 *
 * @param id The unique identifier for the web server.
 */
WebServer::WebServer(int id) : server_id(id), available(true) {}

/**
 * @brief Takes a request for processing.
 *
 * This function accepts a Request object, marks the server as unavailable,
 * and processes the request.
 *
 * @param request The request to be processed by the server.
 */
void WebServer::takeRequest(const Request& request) {
    available = false;  // Mark server as unavailable
    std::cout << "WebServer " << server_id << " received a request." << std::endl;
    processRequest(request);  // Process the incoming request
}

/**
 * @brief Check if the server is available.
 *
 * @return true if the server is available; false otherwise.
 */
bool WebServer::isAvailable() const {
    return available;  // Return the availability status of the server
}

/**
 * @brief Processes the given request.
 *
 * This function simulates processing of the provided request. It prints
 * the request details, sleeps for the specified processing time, and
 * marks the server as available after processing.
 *
 * @param request The request to be processed.
 */
void WebServer::processRequest(const Request& request) {
    std::cout << "WebServer " << server_id << " processing request: ";
    request.print();  // Print request details
    std::this_thread::sleep_for(std::chrono::milliseconds(request.time));  // Simulate processing
    std::cout << "WebServer " << server_id << " finished processing." << std::endl;
    available = true;  // Mark server as available after processing
}

/**
 * @brief Retrieve the unique ID of the WebServer.
 *
 * This function returns the unique identifier of the WebServer instance,
 * which was assigned during its creation.
 *
 * @return int The unique ID of the WebServer.
 */
int WebServer::getID() const {
    return server_id;
}

