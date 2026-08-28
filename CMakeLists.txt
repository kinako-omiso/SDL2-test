cmake_minimum_required(VERSION 3.16)

project(sdl_sample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# clangdが利用するデータベースを生成
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(sdl_sample
  src/main.cpp
)

target_link_libraries(sdl_sample
  PRIVATE
  SDL2::SDL2
)
