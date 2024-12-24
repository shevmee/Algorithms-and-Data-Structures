cmake_minimum_required(VERSION 3.10)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(gtest)

# cmake .. -DCMAKE_BUILD_TYPE=Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address,undefined")

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
        set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=memory")
    endif()

    message(STATUS "Sanitizers enabled: AddressSanitizer and UndefinedBehaviorSanitizer")
else()
    message(STATUS "Sanitizers are only enabled in Debug mode")
endif()

add_executable(BigInteger main.cpp src/BigInteger.cpp)
target_include_directories(BigInteger PRIVATE include)

add_executable(BigIntegerTests test/test_main.cpp src/BigInteger.cpp)
target_include_directories(BigIntegerTests PRIVATE include)

target_link_libraries(BigIntegerTests gtest gtest_main)


enable_testing()
add_test(NAME BigIntegerTests COMMAND BigIntegerTests)
