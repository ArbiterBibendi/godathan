
if(NOT "/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitinfo.txt" IS_NEWER_THAN "/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/drake/projects/godathan/lib/sleepy-discord/deps/opus"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/drake/projects/godathan/lib/sleepy-discord/deps/opus'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout "https://gitlab.xiph.org/xiph/opus.git" "opus"
    WORKING_DIRECTORY "/home/drake/projects/godathan/lib/sleepy-discord/deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://gitlab.xiph.org/xiph/opus.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout 7628d844 --
  WORKING_DIRECTORY "/home/drake/projects/godathan/lib/sleepy-discord/deps/opus"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '7628d844'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/drake/projects/godathan/lib/sleepy-discord/deps/opus"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/drake/projects/godathan/lib/sleepy-discord/deps/opus'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitinfo.txt"
    "/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/drake/projects/godathan/build/opus-download/opus-download-prefix/src/opus-download-stamp/opus-download-gitclone-lastrun.txt'")
endif()

