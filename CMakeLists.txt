# Requirement
cmake_minimum_required(VERSION 2.8)

# Project configuration
project(Minecraft)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Minecraft/bin/tmp)

find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
	message(STATUS "OpenGL found")
endif()

include_directories( # Search directories for .h files
	${OPENGL_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Minecraft/src
    	${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/include
       ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/include
       ${CMAKE_SOURCE_DIR}/Minecraft/vendor
)

add_subdirectory(Minecraft/vendor/ImGUI)
add_subdirectory(Minecraft/vendor/stb_image)
add_subdirectory(Minecraft/vendor/octree)

set(ALL_LIBRARIES 
       ImGUI
       stb_image
	octree
       ${OPENGL_LIBRARIES}
       ${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2.lib
	${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2main.lib
       ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/lib/Debug/x64/glew32d.lib
       )

# Build
add_subdirectory(Minecraft/src)







