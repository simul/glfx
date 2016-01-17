cmake_minimum_required(VERSION 2.8.7)

project(glfx)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

set(GLFX_VERSION 0.7.5)

SET (OPENGL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../OpenGL" CACHE PATH "")
SET (GLEW_DIR "${CMAKE_SOURCE_DIR}/../glew" CACHE PATH "")
SET (GLEW_LIB_DIR "${CMAKE_SOURCE_DIR}/../glew/lib" CACHE PATH "")

SET (GLSLANG_DIR "${CMAKE_SOURCE_DIR}/../glslang" CACHE PATH "")
SET (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
SET (LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name")
## the following are directories where stuff will be installed to
SET(INCLUDE_INSTALL_DIR      "${CMAKE_INSTALL_PREFIX}/include/GL/" CACHE PATH "The subdirectory to the header prefix")
SET(PKGCONFIG_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

IF(NOT WIN32)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/glfx.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/glfx.pc @ONLY)
  INSTALL( FILES ${CMAKE_CURRENT_BINARY_DIR}/glfx.pc DESTINATION ${PKGCONFIG_INSTALL_PREFIX})
ENDIF(NOT WIN32)

add_subdirectory(src)

add_subdirectory(examples)