cmake_minimum_required(VERSION 3.26)
project(CSC381)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)

FetchContent_Declare(
        GLFW
        GIT_REPOSITORY https://github.com/glfw/glfw.git
)

FetchContent_Declare(
        GLEW
        GIT_REPOSITORY https://github.com/nigels-com/glew.git
)

#FetchContent_Declare(
#        GLM
#        GIT_REPOSITORY https://github.com/g-truc/glm.git
#)

FetchContent_MakeAvailable(GLEW GLFW)

add_executable(
        main
        main.cpp
        transform.cpp
        transform.h
)

target_link_libraries(main PRIVATE GLEW glfw GL)

target_include_directories(main PRIVATE "${GLEW_SOURCE_DIR}/include")
target_include_directories(main PRIVATE "${GLFW_SOURCE_DIR}/include")

#target_include_directories(main PRIVATE "${GLM_SOURCE_DIR}")
