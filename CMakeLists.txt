project(conway)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/sdl_wrapper.cpp
    src/game_of_life.cpp
    src/view.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(EMSCRIPTEN)
  set(SDL2_HEADERS "")
  find_path(SDL2_HEADERS "SDL2/SDL.h")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_HEADERS})
  target_link_libraries(${PROJECT_NAME} "-s USE_SDL=2 -o index.html")
else()
  find_package(SDL2 REQUIRED)
  target_link_libraries(${PROJECT_NAME} SDL2)
endif()
