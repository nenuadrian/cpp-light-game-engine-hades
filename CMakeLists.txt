cmake_minimum_required( VERSION 2.8 )

project( HADES )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")


add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(server)

add_subdirectory(editor)
