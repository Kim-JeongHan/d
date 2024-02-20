#ifndef CONNECTOR_MANAGER_RB_HPP
#define CONNECTOR_MANAGER_RB_HPP

#include <iostream>
#include <memory>

// socket
#include <sys/socket.h>
#include <arpa/inet.h>


#include "connector/manager.hpp"
#include "connector/protocol/rainbow.hpp"

namespace DDECK
{
namespace CONNECTOR
{
class ManagerRB : public Manager
{
public:
        ManagerRB();
        ManagerRB(const std::string & ip, const int & port);
        ~ManagerRB();
        

        void run();
        void runSocket();
        void setDataType(const std::shared_ptr<RAINBOW::Data_RB> & data_rb);

private:
        int sock_data_, sock_command_;
        std::shared_ptr<RAINBOW::Data_RB> data_rb_;
        struct sockaddr_in server_data_;
        
        bool CreateSocket_();


        void signalHandler_(int signum);
};     // manager
}      // namespace CONNECTOR
}      // namespace DDECK
#endif // CONNECTOR_MANAGER_RB_HPP