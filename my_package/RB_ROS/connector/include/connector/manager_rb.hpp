#ifndef CONNECTOR_MANAGER_RB_HPP
#define CONNECTOR_MANAGER_RB_HPP

#define RB_CMD_PORT 5000
#define RB_DATA_PORT 5001

#include <iostream>
#include <memory>

#include "connector/manager.hpp"
#include "connector/protocol/rainbow.hpp"

namespace DDECK
{
namespace CONNECTOR
{
class ManagerRB : public Manager
{
public:
    ManagerRB(const std::string & ip);
    
    ~ManagerRB();

    //TODO: void ReciveData()
    //TODO: void UpdateData()
    //TODO: std::shared_ptr<RAINBOW::Data_RB> getData()

    //TODO: void setData(const std::shared_ptr<RAINBOW::Data_RB> & data_rb)
    //TODO: void sendCommand(const std::string & idx)
    
    void setDataType(const std::shared_ptr<RAINBOW::Data_RB> & data_rb);

private:
    int sock_data_, sock_command_;
    std::shared_ptr<RAINBOW::Data_RB> data_rb_;
    struct sockaddr_in server_data_;
    

};     // manager
}      // namespace CONNECTOR
}      // namespace DDECK
#endif // CONNECTOR_MANAGER_RB_HPP