# Project-wide CMake for Zengine
# author: Chris Zehr, chris.zzehr@gmail.com
# 2/18/2016

cmake_minimum_required (VERSION 2.8)
project (Zengine)

#Set output of final executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../bin)

###################################################################################

#Find include directories for OpenGL
find_package(OpenGL REQUIRED)
IF(APPLE)
     SET(CMAKE_CXX_LINK_FLAGS "-framework OpenGL -framework GLUT")
     ADD_EXECUTABLE(mesh_view mesh_view.cpp)
ENDIF(APPLE)
if (OPENGL_FOUND)
    MESSAGE("OpenGL Correctly Found")
else (OPENGL_FOUND)
    MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

# Find include directories for SDL2
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_BINARY_DIR}/CMakeScripts")
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    MESSAGE("SDL2 Correctly Found")
else (SDL2_FOUND)
    MESSAGE("SDL2 environment missing")
endif (SDL2_FOUND)

###################################################################################

# Get all Server include directories
file(GLOB_RECURSE Server_HEADERS RELATIVE "../src/server" *h )
set(Server_INCLUDE_DIRS "")
foreach(headerFile ${Server_HEADERS})
    get_filename_component(headerDirectory ${headerFile} PATH)
    list (APPEND Server_INCLUDE_DIRS ${headerDirectory})
endforeach()
list(REMOVE_DUPLICATES Server_INCLUDE_DIRS)

# Get all Client include directories
file(GLOB_RECURSE Client_HEADERS RELATIVE "../src/client" *h )
set(Client_INCLUDE_DIRS "")
foreach(headerFile ${Client_HEADERS})
    get_filename_component(headerDirectory ${headerFile} PATH)
    list (APPEND Client_INCLUDE_DIRS ${headerDirectory})
endforeach()
list(REMOVE_DUPLICATES Client_INCLUDE_DIRS)

# Get all sources for Server and Client
file(GLOB_RECURSE Server_SOURCES RELATIVE "../src/server" *cpp )
file(GLOB_RECURSE Client_SOURCES RELATIVE "../src/client" *cpp )

###################################################################################

# Add executables for Server and Client
add_executable(ZengineServer ${Server_SOURCES} ../src/server/ZengineServer.cpp )
add_executable(ZengineClient ${Client_SOURCES} ../src/client/ZengineClient.cpp )

# Add include directories for Server and Client
target_include_directories(ZengineServer PRIVATE ${Server_INCLUDE_DIRS})
target_include_directories(ZengineClient PRIVATE ${Client_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} )

# Link Libraries for Client
target_link_libraries (ZengineClient ${SDL2_LIBRARY} ${OPENGL_LIBRARIES}  )

###################################################################################