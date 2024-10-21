#include "request.h"
#include <iostream>

/**
 * @brief Print the details of the Request.
 *
 * This function prints the input IP address, output IP address, processing
 * time, and job type to the standard output (console).
 */
void Request::print() const {
    std::cout << "IP In: \n" << ip_in << ", IP Out: \n" << ip_out 
              << ", Time: \n" << time << ", Job Type: \n" << job_type 
              << std::endl;
}
