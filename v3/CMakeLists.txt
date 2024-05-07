cmake_minimum_required(VERSION 3.10)
project(CaDBR) #Omniscient pool

include(FetchContent)
add_compile_options(-std=c++11 -g)
include_directories(
        Config
        Pool
        User
        Strategy
)
add_executable(${PROJECT_NAME}
        Pool/pool.cpp
        User/User.cpp
        Strategy/Strategy.cpp
        main.cpp)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
    message(STATUS "Fetching yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
