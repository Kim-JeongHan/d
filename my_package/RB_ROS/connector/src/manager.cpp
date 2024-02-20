
#include "connector/manager.hpp"

using namespace DDECK::CONNECTOR;

Manager::Manager(const std::string & ip,
                 const int & port)
: ip_(ip),
  port_(port)
{
}


Manager::~Manager()
{
}


void Manager::run()
{
}
