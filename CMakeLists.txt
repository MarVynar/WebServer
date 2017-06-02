cmake_minimum_required (VERSION 2.8.1)

project(WebServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_executable(MyWebServerExecutable main.cpp request.cpp MyWebServer.cpp response.cpp)