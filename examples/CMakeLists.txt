
link_directories( "${LIB_DESTINATION}/${CMAKE_CONFIGURATION}" )
link_libraries(glfx)

include_directories("${GLFX_SOURCE_DIR}/include")

SET (GLFW_DIR "${CMAKE_SOURCE_DIR}/../glfw" CACHE PATH "")
SET (GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/../glfw/build" CACHE PATH "")

SET (GLEW_BIN_DIR "${CMAKE_SOURCE_DIR}/../glew/bin" CACHE PATH "")


include_directories( "./../include" )
include_directories("${GLFW_DIR}/include")
if ("${OPENGL_INCLUDE_DIR}")
    include_directories("${OPENGL_INCLUDE_DIR}")
endif()

link_directories( "${GLFW_LIB_DIR}/${CMAKE_CONFIGURATION}" )
link_libraries("glfw3")

IF(WIN32)
	include_directories("${GLEW_DIR}/include")
	link_directories( "${GLEW_DIR}/lib" )
	link_directories( "${GLEW_LIB_DIR}" )
ENDIF(WIN32)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

FILE( GLOB EFFECT_FILES "*.sfx" )

SOURCE_GROUP( "Shaders" FILES ${EFFECT_FILES} )

FILE( GLOB COMMON_HEADER_FILES
"*.h"
)
SOURCE_GROUP( "Header Files" FILES ${COMMON_HEADER_FILES} )

add_executable(triangle WIN32 MACOSX_BUNDLE Triangle.cpp ${COMMON_HEADER_FILES} ${EFFECT_FILES})

set(WINDOWS_BINARIES triangle)

set_target_properties(${WINDOWS_BINARIES} PROPERTIES FOLDER "glfx/examples")

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (APPLE)
    set_target_properties(triangle PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Triangle")

    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFX_VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFX_VERSION_FULL}
                          MACOSX_BUNDLE_INFO_PLIST "${GLFX_SOURCE_DIR}/CMake/MacOSXBundleInfo.plist.in")
endif()

