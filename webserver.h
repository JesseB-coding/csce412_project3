#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

/**
 * @class WebServer
 * @brief Represents a web server that processes requests.
 *
 * The WebServer class manages incoming requests and keeps track of its 
 * availability status. It provides functionality to take and process 
 * requests from the LoadBalancer.
 */
class WebServer {
    public:
        /**
         * @brief Construct a new WebServer object.
         *
         * Initializes the web server with a unique identifier and sets its
         * availability status to true.
         *
         * @param id The unique identifier for the web server.
         */
        WebServer(int id);

        /**
         * @brief Takes a request for processing.
         *
         * This function accepts a Request object and queues it for processing.
         *
         * @param request The request to be processed by the server.
         */
        void takeRequest(const Request& request);

        /**
         * @brief Check if the server is available.
         *
         * @return true if the server is available; false otherwise.
         */
        bool isAvailable() const;

        /**
         * @brief Processes the given request.
         *
         * This function processes the provided request and updates the 
         * server's availability status accordingly.
         *
         * @param request The request to be processed.
         */
        void processRequest(const Request& request);
        
        /**
         * @brief Get the unique identifier of the web server.
         *
         * This function returns the ID assigned to the web server,
         * which is used to distinguish between different servers.
         *
         * @return int The ID of the web server.
         */
        int getID() const;


    private:
        int server_id;  ///< The unique identifier for the web server.
        bool available;  ///< Availability status of the server (true if available).
};

#endif
