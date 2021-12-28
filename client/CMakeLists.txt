cmake_minimum_required( VERSION 2.8 )

project( HADES-CLIENT )

if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_F LAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

set( HADES-CLIENT-SRC
     main.cpp)
LINK_LIBRARIES(
	HADES-CORE 
)
add_executable( HADES-CLIENT ${HADES-CLIENT-SRC}   )
target_link_libraries( HADES-CLIENT HADES-CORE  )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HADES-CLIENT)
