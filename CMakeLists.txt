cmake_minimum_required(VERSION 3.0.0)

project(GoGame VERSION 0.1.0)
set(NAME ${CMAKE_PROJECT_NAME})

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "origin/master"
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/sfml"
)

FetchContent_MakeAvailable(sfml)

file(
    GLOB 
    SOURCES 
    src/*.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${NAME} ${SOURCES})

target_link_libraries(
    ${NAME} 
    sfml-audio 
    sfml-graphics 
    sfml-network 
    sfml-system 
    sfml-window
)


