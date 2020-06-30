cmake_minimum_required(VERSION 3.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
project(godathan)

add_executable(godathan src/main.cpp src/godathan.cpp src/voiceeventhandler.cpp)
option(ENABLE_VOICE ON)
target_include_directories(godathan PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/sleepy-discord)
target_link_libraries(godathan sleepy-discord)

execute_process(COMMAND curl -L https://yt-dl.org/downloads/latest/youtube-dl -o ${CMAKE_SOURCE_DIR}/externals/youtube-dl/youtube-dl)
execute_process(COMMAND chmod a+rx ${CMAKE_SOURCE_DIR}/externals/youtube-dl/youtube-dl)
