#ifndef CONNECTOR_MANAGER_HPP
#define CONNECTOR_MANAGER_HPP

#include <string>
#include <signal.h>
#include <stdio.h>


namespace DDECK
{
namespace CONNECTOR
{
class Manager
{
public:
        Manager(const std::string & ip,
                const int & port);
        Manager();
        ~Manager();
        
        void run();
protected:        
        std::string ip_;
        int port_;
private:
        virtual void signalHandler_(int signum) = 0;
};     // manager
}      // namespace CONNECTOR
}      // namespace DDECK
#endif // CONNECTOR_MANAGER_HPP