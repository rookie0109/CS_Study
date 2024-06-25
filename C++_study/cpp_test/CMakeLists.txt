cmake_minimum_required(VERSION 2.8.3)
project(cpp_test)

set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OsqpEigen REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${OsqpEigen_INCLUDE_DIRS}
  )

add_executable(test_node test1.cpp)
add_executable(test_osqp test.cpp)


add_executable(test_po test_polymorphism.cpp)

target_link_libraries(test_osqp OsqpEigen::OsqpEigen)
# target_link_libraries(test_node ${OpenCV_LIBS} ${catkin_LIBRARIES})


# add_executable(gen_prm cv_prm.cpp)
# target_link_libraries(gen_prm ${OpenCV_LIBS})
