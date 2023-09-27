# Copyright © 2023 Alexandre Coderre-Chabot
#
# This file is licensed under the MIT license. For more information, visit:
#     https://mit-license.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#   - The above copyright notice and this permission notice shall be included in
#     all copies or substantial portions of the Software.
#   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#     FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#     DEALINGS IN THE SOFTWARE.
#
# This file was originally obtained from:
#     https://github.com/acodcha/secret-santa

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define the global settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wextra -Wno-return-type -Wpedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the Secret Santa project and its options.
project(
  "secret-santa"
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "Organizes a Secret Santa gift exchange event!"
  HOMEPAGE_URL "https://github.com/acodcha/secret-santa"
)
option(
  TEST_SECRET_SANTA
  "Configure the Secret Santa tests."
  OFF
)

# Download and setup the yaml-cpp library.
include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)
message(STATUS "The yaml-cpp library was fetched from: https://github.com/jbeder/yaml-cpp.git")

# Define the Secret Santa Randomizer executable.
add_executable(secret-santa-randomizer ${PROJECT_SOURCE_DIR}/source/Randomizer/Main.cpp)
target_link_libraries(secret-santa-randomizer PUBLIC stdc++fs yaml-cpp)

# Define the Secret Santa Messenger executable.
add_executable(secret-santa-messenger ${PROJECT_SOURCE_DIR}/source/Messenger/Main.cpp)
target_link_libraries(secret-santa-messenger PUBLIC stdc++fs yaml-cpp)

# Configure the Secret Santa tests.
if(TEST_SECRET_SANTA)
  # Search for the GoogleTest library.
  find_package(GTest QUIET)

  if(GTest_FOUND)
    message(STATUS "The GoogleTest library was found at: ${GTest_CONFIG}")
  else()
    # In this case, the GoogleTest library is not found, so fetch it instead.
    FetchContent_Declare(
      GoogleTest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG main
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(GoogleTest)
    message(STATUS "The GoogleTest library was fetched from: https://github.com/google/googletest.git")
  endif()

  # Include the GoogleTest library and enable testing.
  include(GoogleTest)
  enable_testing()

  # Define the Secret Santa test executables.

  add_executable(messenger_settings ${PROJECT_SOURCE_DIR}/test/Messenger/Settings.cpp)
  target_link_libraries(messenger_settings GTest::gtest_main)
  gtest_discover_tests(messenger_settings)

  add_executable(randomizer_settings ${PROJECT_SOURCE_DIR}/test/Randomizer/Settings.cpp)
  target_link_libraries(randomizer_settings GTest::gtest_main)
  gtest_discover_tests(randomizer_settings)

  add_executable(string ${PROJECT_SOURCE_DIR}/test/String.cpp)
  target_link_libraries(string GTest::gtest_main)
  gtest_discover_tests(string)

  message(STATUS "The Secret Santa tests were configured. Build the tests with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "The Secret Santa tests were not configured. Run \"cmake .. -DTEST_SECRET_SANTA=ON\" to configure the tests.")
endif()
