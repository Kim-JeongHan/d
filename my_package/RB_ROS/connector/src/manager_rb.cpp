#include "connector/manager_rb.hpp"

using namespace DDECK::CONNECTOR;

ManagerRB::ManagerRB(const std::string & ip)
: Manager(ip)
{
    this->data_rb_ = std::make_shared<RAINBOW::Data_RB>();

    // Create command socket
    this->createSocketdesc_("command");
    this->createServerData_("command", ip_, RB_CMD_PORT);
    this->createSocket("command");

    // Create data socket
    this->createSocketdesc_("data");
    this->createServerData_("data", ip_, RB_DATA_PORT);
    this->createSocket("data");



}




ManagerRB::~ManagerRB()
{
}



void ManagerRB::setDataType(const std::shared_ptr<RAINBOW::Data_RB> & data_rb)
{
    data_rb_ = data_rb;
}




{
    fd_set readfds, writefds;
    struct timeval tv;
    int error;
    // Set non-blocking socket
    int flag = fcntl(sock_desc, F_GETFL, 0);
    fcntl(sock_desc, F_SETFL, flag | O_NONBLOCK);

    int status = connect(sock_desc, (struct sockaddr *)&server_data, sizeof(server_data));
    if (status < 0)
    {
        if (errno != EINPROGRESS)
        {
            std::cout << "ERROR - rb_connector socket connection failed." << std::endl;
            return (-10);
        }
    }

    if(status == 0)
    {
        std::cout << "rb_connector socket connected." << std::endl;
        goto done;
    }

    FD_ZERO(&readfds);
    FD_SET(sock_desc, &writefds);
    tv.tv_sec = nsec;
    tv.tv_usec = 0;
    
    if(select(sock_desc + 1, &readfds, &writefds, NULL, nsec ? &tv : NULL) == 0)
    {
        close(sock_desc);
        errno = ETIMEDOUT;
        std::cout << "ERROR - rb_connector socket connection timeout." << std::endl;
        return (-11);
    }
    if (FD_ISSET(sock_desc, &writefds) || FD_ISSET(sock_desc, &readfds))
    {
        socklen_t len = sizeof(error);
        if (getsockopt(sock_desc, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
            std::cout << "ERROR - rb_connector solaris getsockopt failed." << std::endl;
            return (-12);
        }
    }
    else
    {
        std::cout << "ERROR - rb_connector select error." << std::endl;
        return (-13);
    }

done:
    // Set blocking socket
    fcntl(sock_desc, F_SETFL, flag);
    if(error)
    {
        close(sock_desc);
        errno = error;
        std::cout << "ERROR - rb_connector socket connection failed." << std::endl;
        return (-14);
    }
    return 0;
}



