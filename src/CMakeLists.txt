project(octomap_local)

set(octomap_SRCS ColorOctreeImpl.cpp colortable.cpp octo_globaldef.cpp)
add_library(octomap_local ${octomap_SRCS})
target_link_libraries(octomap_local ${catkin_LIBRARIES})

add_executable(test_ot test_ot.cpp)
target_link_libraries(test_ot octomap_local octomap octomath)
