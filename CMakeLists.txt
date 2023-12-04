cmake_minimum_required(VERSION 3.22)
project(TCP_Snake)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4.5.4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} /opt)
add_executable(TCP_Snake src/main.cpp src/game.cpp include/game.h src/snake.cpp include/snake.h src/TCP.cpp include/TCP.h)
target_link_libraries(TCP_Snake ${OpenCV_LIBS})
