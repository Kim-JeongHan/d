cmake_minimum_required(VERSION 2.8.3)
project(rb_connector)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  actionlib_msgs
  actionlib
)
find_package(Qt5 COMPONENTS Core Quick  REQUIRED)


add_message_files(
  FILES
  rb_data.msg
  rb_command.msg
)

generate_messages(DEPENDENCIES std_msgs)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package(
    CATKIN_DEPENDS
    roscpp
    std_msgs
    actionlib_msgs
    actionlib
)

##############################################################################
# Qt Environment
##############################################################################


include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS})

add_executable(rb_connector src/rb_connector.cpp)
target_link_libraries(rb_connector 
    ${catkin_LIBRARIES} 
    Qt5::Core
    Qt5::Quick

  )

add_dependencies(rb_connector rb_connector_generate_messages_cpp)


