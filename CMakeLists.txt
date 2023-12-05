cmake_minimum_required(VERSION 3.22)
project(TCP_Snake)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4.5.4 REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} /opt)
add_executable(TCP_Snake src/main.cpp src/game.cpp include/game.h src/snake.cpp include/snake.h src/TCP.cpp include/TCP.h)
target_link_libraries(TCP_Snake PRIVATE ${OpenCV_LIBS} Boost::log)
