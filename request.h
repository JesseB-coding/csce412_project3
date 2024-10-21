#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

/**
 * @struct Request
 * @brief Struct representing a network request.
 *
 * The Request struct holds information about an IP address, processing time,
 * and the job type for a network request.
 */
struct Request {
    string ip_in;   ///< The input IP address.
    string ip_out;  ///< The output IP address.
    int time;       ///< Time required to process the request.
    char job_type;  ///< Job type ('P' for processing, 'S' for streaming).

    /**
     * @brief Construct a new Request object.
     *
     * @param in The input IP address.
     * @param out The output IP address.
     * @param t The time required to process the request.
     * @param jt The job type ('P' for processing, 'S' for streaming).
     */
    Request(const std::string& in, const std::string& out, int t, char jt)
        : ip_in(in), ip_out(out), time(t), job_type(jt) {}

    /**
     * @brief Print the details of the request.
     *
     * This function prints the input and output IP addresses, the processing
     * time, and the job type to the console.
     */
    void print() const;
};

#endif
