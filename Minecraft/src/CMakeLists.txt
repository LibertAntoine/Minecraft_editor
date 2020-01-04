#file(GLOB HEADER_FILES *.h forms/*.h modes/*.h Renderer/*.h Interaction/*.h)
#file(GLOB SRC_FILES *.cpp forms/*.cpp modes/*.cpp Renderer/*.cpp Interaction/*.cpp)

file(GLOB HEADER_FILES *.h GraphicEngine/*.h modes/*.h MinecraftEditor/Interaction/*.h MinecraftEditor/Graphic/Forms/*.h MinecraftEditor/Graphic/Lights/*.h MinecraftEditor/Graphic/Renderers/*.h)
file(GLOB SRC_FILES *.cpp GraphicEngine/*.cpp modes/*.cpp MinecraftEditor/Interaction/*.cpp MinecraftEditor/Graphic/Forms/*.cpp MinecraftEditor/Graphic/Lights/*.cpp MinecraftEditor/Graphic/Renderers/*.cpp)

add_executable(Minecraft
    ${SRC_FILES}
    ${HEADER_FILES}
)

target_link_libraries(Minecraft
    ${ALL_LIBRARIES}
)

# https://stackoverflow.com/a/50882216/11106413
if (MSVC)
	target_compile_options(Minecraft PRIVATE /W4 /WX)
else()
	target_compile_options(Minecraft PRIVATE -W -Wall)
endif()


file(COPY ${CMAKE_SOURCE_DIR}/WinDependencies/glew-2.1.0/bin/${CMAKE_BUILD_TYPE}/x64/glew32d.dll
DESTINATION ./
)

file(COPY ${CMAKE_SOURCE_DIR}/WinDependencies/SDL2/x64/SDL2.dll
DESTINATION ./
)
