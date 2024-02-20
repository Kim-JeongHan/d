#ifndef CONNECTOR_MANAGER_HPP
#define CONNECTOR_MANAGER_HPP

#include <iostream>
#include <memory>
#include <unordered_map>

#include <string>
#include <signal.h>
#include <stdio.h>

// socket
#include <sys/socket.h>
#include <arpa/inet.h>


// non-blocking socket
#include <unistd.h> 
#include <fcntl.h> 


namespace DDECK
{
namespace CONNECTOR
{
class Manager
{
public:
    Manager(const std::string & ip);
    Manager();
    ~Manager();
    
    


    bool createSocket(const std::string & idx);
    int connectSocket(const int & sock_desc, 
                       const struct sockaddr_in & server_data,
                       const int & nsec);
    //TODO: int connect2server_data(const std::string & idx)

protected:        
    std::string ip_;

    bool createSocketdesc_(const std::string & idx);   
    bool createServerData_(const std::string & idx,
                           const std::string & ip,
                           const int & port);   
private:

    void signalHandler_(int signum);

    virtual void signalHandler_(int signum);

    std::unordered_map<std::string, int> sock_desc_;
    std::unordered_map<std::string, struct sockaddr_in> server_data_;
};     // manager
}      // namespace CONNECTOR
}      // namespace DDECK
#endif // CONNECTOR_MANAGER_HPP