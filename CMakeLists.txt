cmake_minimum_required(VERSION 3.14)

project(ForSightRoboticsProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cc
    main_storage.cc
    task.cc
    task_queue_manager.cc
)

add_executable(waves_maker ${SOURCES})
target_link_libraries(waves_maker pthread)
target_compile_options(waves_maker PRIVATE -pedantic-errors)
