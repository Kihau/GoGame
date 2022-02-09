cmake_minimum_required(VERSION 3.0.0)

project(GoGame VERSION 0.1.0)
set(EXEC ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(sfml
    GIT_REPOSITORY "https://github.com/Kihau/SFML.git"
    # GIT_TAG "master"
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/sfml"
)

FetchContent_MakeAvailable(sfml)

file(
    GLOB 
    SOURCES 
    src/*.cpp
)

file(
    GLOB 
    GUI 
    src/gui/*.cpp
)

file(
    GLOB 
    STATES 
    src/states/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include/)
add_executable(${EXEC} ${SOURCES} ${STATES} ${GUI})

target_link_libraries(
    ${EXEC} 
    sfml-audio 
    sfml-graphics 
    sfml-network 
    sfml-system 
    sfml-window
)

# add_custom_target(copy_res
#     COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/copy-res.cmake
# )

# add_dependencies(${EXEC} copy_res)

add_custom_command(
    TARGET ${EXEC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${EXEC}>/resources
)


