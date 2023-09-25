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
  DESCRIPTION "Sends email messages for organizing a Secret Santa gift exchange event!"
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

# Define the main Secret Santa executable.
add_executable(secret-santa ${PROJECT_SOURCE_DIR}/source/Main.cpp)
target_link_libraries(secret-santa PUBLIC stdc++fs yaml-cpp)

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

  add_executable(example ${PROJECT_SOURCE_DIR}/test/Example.cpp)
  target_link_libraries(example GTest::gtest_main)
  gtest_discover_tests(example)

  message(STATUS "The Secret Santa tests were configured. Build the tests with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "The Secret Santa tests were not configured. Run \"cmake .. -DTEST_SECRET_SANTA=ON\" to configure the tests.")
endif()
