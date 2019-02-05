project(logger)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_library(logger src/logger.cpp)

install (TARGETS logger DESTINATION "lib")
