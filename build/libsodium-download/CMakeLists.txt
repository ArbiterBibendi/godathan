# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(libsodium-download NONE)

include(ExternalProject)
ExternalProject_Add(libsodium-download
                    GIT_REPOSITORY;https://github.com/jedisct1/libsodium.git;GIT_TAG;stable;UPDATE_DISCONNECTED;1
                    SOURCE_DIR          "/home/drake/projects/godathan/lib/sleepy-discord/deps/libsodium"
                    BINARY_DIR          "/home/drake/projects/godathan/build/libsodium-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
