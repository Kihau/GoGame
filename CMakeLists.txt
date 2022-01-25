cmake_minimum_required(VERSION 3.0.0)

project(GoGame VERSION 0.1.0)
set(EXEC ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.1"
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/sfml"
)

FetchContent_MakeAvailable(sfml)

file(
    GLOB 
    SOURCES 
    src/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${EXEC} ${SOURCES})

target_link_libraries(
    ${EXEC} 
    sfml-audio 
    sfml-graphics 
    sfml-network 
    sfml-system 
    sfml-window
)

add_custom_command(
    TARGET ${EXEC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${EXEC}>/resources
)


