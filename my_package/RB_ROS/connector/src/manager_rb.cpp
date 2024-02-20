#include "connector/manager_rb.hpp"

using namespace DDECK::CONNECTOR;

ManagerRB::ManagerRB()
: Manager()
{
        this->data_rb_ = std::make_shared<RAINBOW::Data_RB>();
}

ManagerRB::ManagerRB(const std::string & ip,
                     const int & port)
: Manager(ip, port)
{
        this->data_rb_ = std::make_shared<RAINBOW::Data_RB>();
}


ManagerRB::~ManagerRB()
{
}

void ManagerRB::run()
{
}

void ManagerRB::runSocket()
{
        // If the socket is not created, create it.
        if(sock_command_==0)
        {
                CreateSocket_();
        }

}

void ManagerRB::setDataType(const std::shared_ptr<RAINBOW::Data_RB> & data_rb)
{
        data_rb_ = data_rb;
}

bool ManagerRB::CreateSocket_(const int & port)
{
        /*
        socket
        PF_INET: IPv4 protocols(Protocol Family)
        SOCK_DGRAM: UDP(User Datagram Protocol)
        */
        sock_data_ = socket(PF_INET, SOCK_DGRAM, 0);
        if (sock_data_ < 0)
        {
                std::cout << "ERROR - rb_connector sock_data is not created." << std::endl;
                return false;
        }
        /*
        s_addr : 32bit IPv4 address
        PF_INET : IPv4 protocols(Protocol Family)
        htons : host to network short
        */
        server_data_.sin_addr.s_addr = inet_addr(ip_.c_str());
        server_data_.sin_family = PF_INET;
        server_data_.sin_port = htons(port_);

        int optval = 1;
        setsockopt(sock_data_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        setsockopt(sock_data_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

        return true;
}



void ManagerRB::signalHandler_(int signum)
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
                        std::cout << "SIGNAL - rb_connector sock_data is shutdown." << std::endl;
                }

                if (shutdown(sock_command_, SHUT_RDWR) == 0)
                {
                        std::cout << "SIGNAL - rb_connector sock_command is shutdown." << std::endl;
                }
                break;
        default:
                break;
        }  
}
