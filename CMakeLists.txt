project(conway)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
  src/init.cpp
  src/events.cpp
  src/render.cpp
  src/window.cpp
  src/game_of_life.cpp
  src/view.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} SDL2)
