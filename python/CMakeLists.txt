include_directories( ${PROJECT_SOURCE_DIR}/include)
include_directories( "/usr/include/eigen3" )
find_package(pybind11)


# pybind11 (version 2.2.1)
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external/pybind11/tools)
include_directories(${PROJECT_SOURCE_DIR}/external/pybind11/include)
include(pybind11Tools)


pybind11_add_module( pangolin pangolin.cpp )
SET_TARGET_PROPERTIES(pangolin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
target_link_libraries( pangolin PRIVATE ${LIBRARY_NAME})