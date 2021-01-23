cmake_minimum_required(VERSION 3.17)

project(pocket)
include_directories(include)
set(POCKET_FILES src/pocket_cube_BFS.c)

add_executable(pocket ${POCKET_FILES})

#set_target_properties(pocket PROPERTIES COMPILE_FLAGS -DCRAQ)
target_link_libraries(pocket m)