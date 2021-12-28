cmake_minimum_required( VERSION 2.8 )

project( HADES-EDITOR )
include_directories( "../core" )
if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_F LAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

set( HADES-EDITOR-SRC
     main.cpp
     )

LINK_LIBRARIES(
HADES-CORE
)

link_directories("../core")


add_executable( HADES-EDITOR ${HADES-EDITOR-SRC}   )

