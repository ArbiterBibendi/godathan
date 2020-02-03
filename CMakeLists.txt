cmake_minimum_required(VERSION 3.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(godathan)

add_executable(godathan src/main.cpp)
#target_include_directories(godathan PUBLIC ${CMAKE_SOURCE_DIR}/lib/sleepy-discord/include/sleepy_discord)
target_include_directories(godathan PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sleepy-discord)
target_link_libraries(godathan sleepy-discord)
