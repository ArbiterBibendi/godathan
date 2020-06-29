# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(opus-download NONE)

include(ExternalProject)
ExternalProject_Add(opus-download
                    GIT_REPOSITORY;https://gitlab.xiph.org/xiph/opus.git;GIT_TAG;7628d844;UPDATE_DISCONNECTED;1
                    SOURCE_DIR          "/home/drake/projects/godathan/lib/sleepy-discord/deps/opus"
                    BINARY_DIR          "/home/drake/projects/godathan/build/opus-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
