# Requirement
cmake_minimum_required(VERSION 3.1)

# Project configuration
project(Minecraft)


# https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake#31010221
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Append compile flags
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fpermissive")

find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
	message(STATUS "OpenGL found")
endif()

# On windows
if (WIN32) 
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/include)
    set(SDL2_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2.lib;
                       ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2main.lib)

# On linux
else()
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
    if(${SDL2_FOUND})
      message(STATUS "SDL2 found")
    endif()
    if(${GLEW_FOUND})
      message(STATUS "GLEW found")
    endif()
endif()


if (WIN32) 
include_directories( # Search directories for .h files
	${OPENGL_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Minecraft/src
    	${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/include
       ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/include
       ${CMAKE_SOURCE_DIR}/Minecraft/vendor
)
else()
  include_directories( # Search directories for .h files
    ${OPENGL_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Minecraft/src
    ${CMAKE_SOURCE_DIR}/Minecraft/vendor
    )
endif()

add_subdirectory(Minecraft/vendor/ImGUI)
add_subdirectory(Minecraft/vendor/stb_image)
add_subdirectory(Minecraft/vendor/octree)

if (WIN32)
  set(ALL_LIBRARIES 
    ImGUI
    stb_image
    ${OPENGL_LIBRARIES}
    ${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2.lib
    ${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2main.lib
    ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/lib/Debug/x64/glew32d.lib
    )
else()
  set(ALL_LIBRARIES 
    ImGUI
    stb_image
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    )
endif()
# Build
add_subdirectory(Minecraft/src)







