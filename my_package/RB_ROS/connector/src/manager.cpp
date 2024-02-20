
#include "connector/manager.hpp"

using namespace DDECK::CONNECTOR;

Manager::Manager(const std::string & ip)
{
        this->ip_ = ip;
}


Manager::~Manager()
{
}




bool Manager::createSocket(const std::string & idx)
{
    /* socker creation
    PF_INET: IPv4 protocols(Protocol Family)
    SOCK_DGRAM: UDP(User Datagram Protocol)
    */
    sock_desc_[idx] = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock_desc_[idx] < 0)
    {
            std::cout << "ERROR - connector socket creation failed." << std::endl;
            return false;
    }
    else
    {
            std::cout << "connector socket descriptor: " << sock_desc_[idx] << std::endl;
    }

    int optval = 1;
    setsockopt(sock_desc_[idx], SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(sock_desc_[idx], SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    return true;
}

int Manager::connectSocket(
    const int & sock_desc, 
    const struct sockaddr_in & server_data,
    const int & nsec
    )
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
            std::cout << "ERROR - connector socket connection failed." << std::endl;
            return (-10);
        }
    }

    if(status == 0)
    {
        std::cout << "connector socket connected." << std::endl;
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
        std::cout << "ERROR - connector socket connection timeout." << std::endl;
        return (-11);
    }
    if (FD_ISSET(sock_desc, &writefds) || FD_ISSET(sock_desc, &readfds))
    {
        socklen_t len = sizeof(error);
        if (getsockopt(sock_desc, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
            std::cout << "ERROR - connector solaris getsockopt failed." << std::endl;
            return (-12);
        }
    }
    else
    {
        std::cout << "ERROR - connector select error." << std::endl;
        return (-13);
    }

done:
    // Set blocking socket
    fcntl(sock_desc, F_SETFL, flag);
    if(error)
    {
        close(sock_desc);
        errno = error;
        std::cout << "ERROR - connector socket connection failed." << std::endl;
        return (-14);
    }
    return 0;
}

bool Manager::createSocketdesc_(const std::string & idx)
{
        sock_desc_[idx] = socket(PF_INET, SOCK_DGRAM, 0);
}

bool Manager::createServerData_(const std::string & idx,
                                const std::string & ip,
                                const int & port)
{
    /* server_data structure
    s_addr : 32bit IPv4 address
    PF_INET : IPv4 protocols(Protocol Family)
    htons : host to network short
    */
        server_data_[idx].sin_addr.s_addr = inet_addr(ip.c_str());
        server_data_[idx].sin_family = PF_INET;
        server_data_[idx].sin_port = htons(port);
}


void Manager::signalHandler_(int signum)
{
        switch (signum)
        {
        case SIGINT:
        case SIGQUIT:
        case SIGABRT:
        case SIGKILL:
        case SIGHUP:
                if (shutdown(sock_data_, SHUT_RDWR) == 0)
                {
                        std::cout << "SIGNAL - connector sock_data is shutdown." << std::endl;
                }

                if (shutdown(sock_command_, SHUT_RDWR) == 0)
                {
                        std::cout << "SIGNAL - connector sock_command is shutdown." << std::endl;
                }
                break;
        default:
                break;
        }  
}