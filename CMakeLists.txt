cmake_minimum_required(VERSION 2.8.3)
project(octomap_local)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(octomap_DIR /opt/ros/hydro/share/octomap)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    pcl_conversions pcl_ros
    roscpp
    sensor_msgs
    nav_msgs
    std_msgs
    message_filters
    tf
    cv_bridge
    octomap
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
# CXX flags
set(CMAKE_CXX_FLAGS "-ggdb -g -O3 -fPIC -fpermissive -std=c++0x -w")


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES sr_slam
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs tf pcl_conversions pcl_ros
  DEPENDS message_runtime std_msgs
#  DEPENDS system_lib
)

# PCL #######################
 set(PCL_DIR "/home/davidz/work/3rdlibs/pcl_1.7.1_src/pcl-pcl-1.7.1/build")
 find_package(PCL 1.7 REQUIRED COMPONENTS common io)
 include_directories(${PCL_INCLUDE_DIRS})
 link_directories(${PCL_LIBRARY_DIRS})
 # add_definitions(${PCL_DEFINITIONS})

###### octomap ######
# link_directories("/opt/ros/hydro/lib")
set(OCTOMAP_LIBRARIES_DIR "/home/davidz/work/3rdlibs/octomap/lib")
link_directories(${OCTOMAP_LIBRARIES_DIR})

add_subdirectory(src)

