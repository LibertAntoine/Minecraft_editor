file(GLOB HEADER_FILES *.h forms/*.h modes/*.h)
file(GLOB SRC_FILES *.cpp forms/*.cpp modes/*.cpp)

add_executable(Minecraft
    ${SRC_FILES}
    ${HEADER_FILES}
)

target_link_libraries(Minecraft
    ${ALL_LIBRARIES}
)


file(COPY ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/bin/${CMAKE_BUILD_TYPE}/x64/glew32d.dll
DESTINATION ./
)

file(COPY ${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2.dll
DESTINATION ./
)
