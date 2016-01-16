cmake_minimum_required(VERSION 2.8.7)

project(glfx)

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../include" )

include_directories("${OPENGL_INCLUDE_DIR}")

include_directories("${GLSLANG_DIR}/include")
 link_directories( "${GLSLANG_DIR}/lib" )

IF(WIN32)
	include_directories("${GLEW_DIR}/include")
	link_directories( "${GLEW_DIR}/lib" )
	link_directories( "${GLEW_LIB_DIR}" )
ENDIF(WIN32)

find_package(FLEX)
if(NOT FLEX_FOUND)
    set(FLEX_EXECUTABLE ../win_flex_bison/win_flex.exe)
    message("Flex not found. Assuming it is at ${FLEX_EXECUTABLE}")
endif()

find_package(BISON)
if(NOT BISON_FOUND)
    set(BISON_EXECUTABLE ../win_flex_bison/win_bison.exe)
    message("Bison not found. Assuming it is at ${BISON_EXECUTABLE}")
endif()

set(PP_LEXED ${CMAKE_CURRENT_BINARY_DIR}/generated/PreprocessLexer.cpp ${CMAKE_CURRENT_BINARY_DIR}/generated/PreprocessLexer.h)
add_custom_command(OUTPUT ${PP_LEXED}
                   COMMAND ${FLEX_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Preprocessor.lpp"
                   MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/Preprocessor.lpp"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)



set(PP_PARSED ${CMAKE_CURRENT_BINARY_DIR}/generated/PreprocessParser.cpp ${CMAKE_CURRENT_BINARY_DIR}/generated/PreprocessParser.h)
add_custom_command(OUTPUT ${PP_PARSED}
                   COMMAND ${BISON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Preprocessor.ypp"
                   MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/Preprocessor.ypp"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)


set(GLFX_LEXED ${CMAKE_CURRENT_BINARY_DIR}/generated/glfxScanner.cpp ${CMAKE_CURRENT_BINARY_DIR}/generated/glfxScanner.h)
add_custom_command(OUTPUT ${GLFX_LEXED}
                   COMMAND ${FLEX_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/glfx.lpp"
                   MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/glfx.lpp"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)



set(GLFX_PARSED ${CMAKE_CURRENT_BINARY_DIR}/generated/glfxLALRParser.cpp ${CMAKE_CURRENT_BINARY_DIR}/generated/glfxLALRParser.hpp)
add_custom_command(OUTPUT ${GLFX_PARSED}
                   COMMAND ${BISON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/glfx.ypp"
                   MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/glfx.ypp"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)


FILE( GLOB GENERATED_FILES
PP_LEXED
PP_PARSED
GLFX_LEXED
GLFX_PARSED
)
SOURCE_GROUP( "Generated Files" FILES ${GENERATED_FILES} )

FILE( GLOB GRAMMAR_FILES
"*.ypp"
"*.lpp"
)
SOURCE_GROUP( "Grammar Files" FILES ${GRAMMAR_FILES} )

FILE( GLOB HEADER_FILES
"../include/gl/glfx.h"
"*.h"
"*.hpp"
)
SOURCE_GROUP( "Header Files" FILES ${HEADER_FILES} )

FILE( GLOB SOURCE_FILES
"*.cpp"
)
SOURCE_GROUP( "Source Files" FILES ${SOURCE_FILES} )


add_library( glfx SHARED ${GRAMMAR_FILES} ${PP_LEXED} ${PP_PARSED} ${GLFX_LEXED} ${GLFX_PARSED} ${HEADER_FILES} ${SOURCE_FILES} )
add_library( glfx_static STATIC ${GRAMMAR_FILES} ${PP_LEXED} ${PP_PARSED} ${GLFX_LEXED} ${GLFX_PARSED} ${HEADER_FILES} ${SOURCE_FILES} )

IF(WIN32)
target_link_libraries( glfx "glew32")
target_link_libraries( glfx "opengl32")
set_target_properties( glfx PROPERTIES COMPILE_FLAGS "-DWIN32 -DUNICODE -D_UNICODE -DGLFX_BUILD" )
set_target_properties( glfx_static PROPERTIES COMPILE_FLAGS "-DWIN32 -DUNICODE -D_UNICODE -DGLFX_BUILD -DGLFX_STATIC -DGLEW_STATIC" )
ELSEIF(UNIX)
target_link_libraries( glfx "GL" "GLEW")
set_target_properties( glfx PROPERTIES COMPILE_FLAGS "-DLINUX -DUNICODE -D_UNICODE -DGLFX_BUILD" )
set_target_properties( glfx_static PROPERTIES COMPILE_FLAGS "-DLINUX -DUNICODE -D_UNICODE -DGLFX_BUILD -DGLFX_STATIC -DGLEW_STATIC" )
ENDIF(WIN32)

IF(NOT WIN32)
INSTALL(FILES ./../include/gl/glfx.h DESTINATION ${INCLUDE_INSTALL_DIR})
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/libglfx_static.a DESTINATION ${LIB_DESTINATION})
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/libglfx.so DESTINATION ${LIB_DESTINATION})
ENDIF(NOT WIN32)
