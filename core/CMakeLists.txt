cmake_minimum_required( VERSION 2.8 )

project( HADES-CORE )

find_package( OpenGL REQUIRED )
set(JSON_BuildTests OFF CACHE INTERNAL "")
option(YAML_CPP_BUILD_TOOLS "Enable testing and parse tools" OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL  "Set when you want to build the OpenGL3+ demos" )
set(BUILD_CPU_DEMOS OFF CACHE BOOL  "Set when you want to build the OpenGL3+ demos" )

OPTION(BUILD_UNIT_TESTS "Build Unit Tests"	OFF)
OPTION(BUILD_OPENGL3_DEMOS "Set when you want to build the OpenGL3+ demos" 	OFF)
include_directories( "glfw/include" 
 "glad/include"
"bullet3"
"imgui"
"imgui/backends"
"glew/include" 

 "openal-soft" 
"openal-soft/include"
"assimp/include" 
 "assimp" 
 "entt" 
"entt/single_include" 
"glm"
"freetype"
 ${OPENGL_INCLUDE_DIRS} 
 "freetype/include" 
 "json/include"
"stb-cmake")

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( BUILD_EXAMPLES OFF CACHE BOOL  " libsonly" )




add_subdirectory( glfw )
add_subdirectory( openal-soft )
add_subdirectory( glm )
add_subdirectory( assimp )
add_subdirectory( bullet3 )
add_subdirectory( glew/build/cmake )
add_subdirectory( entt)

add_subdirectory(json)
add_subdirectory(freetype)

if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()




set( HADES-CORE-SRC
     imgui/imgui.h
     imgui/imgui.cpp
     imgui/imgui_internal.h
   imgui/imgui_tables.cpp
     imgui/imgui_draw.cpp
     imgui/imgui_widgets.cpp
     imgui/imconfig.h
     imgui/backends/imgui_impl_glfw.h
     imgui/backends/imgui_impl_glfw.cpp
     imgui/backends/imgui_impl_opengl2.h
     imgui/backends/imgui_impl_opengl2.cpp

	src/editor.h
	src/editor.cpp
glad/src/glad.c
src/shader.h
src/shader.cpp
src/shader_basic.h
src/shader_basic.cpp
src/shader_complex.h
src/shader_complex.cpp
src/manager.h
src/manager.cpp
src/thing.h
src/thing.cpp
src/physics.h
src/physics.cpp
src/events.h
src/events.cpp
src/asset-manager.h
src/asset-manager.cpp
src/plugin.h
src/sound.h
src/opengl.h
src/sound.cpp
src/model.h
src/model.cpp
src/model_basic.h
src/model_basic.cpp
src/model_complex.h
src/model_complex.cpp
src/scene.h
src/scene.cpp
src/hades.h
src/hades.cpp
src/main.cpp
     )


INCLUDE_DIRECTORIES(
./glad/src
./glew/src
./glm/glm
./freetype/src
./stb-cmake
./openal-soft
./assimp/code
./entt/src
./glfw/src
./bullet3/src
)


LINK_LIBRARIES(
  glm nlohmann_json::nlohmann_json freetype glew_s ${GLEW_LIBRARIES}  OpenAL assimp BulletCollision BulletDynamics LinearMath Bullet3Common
)
add_executable( HADES-CORE ${HADES-CORE-SRC} )

target_compile_features(HADES-CORE PRIVATE cxx_std_17)

target_link_libraries( HADES-CORE ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} glew_s nlohmann_json::nlohmann_json ${GLEW_LIBRARIES} OpenAL assimp glm BulletCollision BulletDynamics LinearMath Bullet3Common)
