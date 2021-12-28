cmake_minimum_required( VERSION 2.8 )

project( HADES-SERVER )
include_directories( "enet/include" )
add_subdirectory(enet)

set( HADES-SERVER-SRC
 
     main.cpp

     )



LINK_LIBRARIES(
  HADES-CORE enet
)
add_executable( HADES-SERVER ${HADES-SERVER-SRC} )

target_link_libraries( HADES-SERVER HADES-CORE  enet)