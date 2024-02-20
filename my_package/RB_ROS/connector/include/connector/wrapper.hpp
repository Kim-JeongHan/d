#ifndef RB_CONNECTOR_WRAPPER_HPP
#define RB_CONNECTOR_WRAPPER_HPP

#include <string>
#include "connector/manager.hpp"


namespace ddeck
{
namespace rb_connector
{
template <class T>
class Wrapper
{
public:
        Wrapper();
        ~Wrapper();
        
        void setRobotType(T * robot_type);
        T getRobotType();

private:


protected:
        T robot_type;


} // wrapper
        
} // namespace rb_connector
} // namespace ddeck
#endif // RB_CONNECTOR_WRAPPER_HPP