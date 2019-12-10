include_directories(./)
file(GLOB_RECURSE SRC_FILES *.cpp *.h)
add_library(stb_image ${SRC_FILES})
