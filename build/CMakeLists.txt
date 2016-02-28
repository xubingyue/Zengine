# Project-wide CMake for Zengine
# author: Chris Zehr, chris.zzehr@gmail.com

cmake_minimum_required (VERSION 2.8)
project (Zengine)

# Set output of final executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

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

# Find include directories for GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    MESSAGE("GLEW Correctly Found")
else (GLEW_FOUND)
    MESSAGE("GLEW environment missing")
endif (GLEW_FOUND)

###################################################################################

# Use custom scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "CMakeScripts")

# Find include directories for SDL2
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    MESSAGE("SDL2 Correctly Found")
else (SDL2_FOUND)
    MESSAGE("SDL2 environment missing")
endif (SDL2_FOUND)

# Find include directories for SDL2_NET
find_package(SDL2_NET REQUIRED)
if (SDL2_NET_FOUND)
    MESSAGE("SDL2_NET Correctly Found")
else (SDL2_NET_FOUND)
    MESSAGE("SDL2_NET environment missing")
endif (SDL2_NET_FOUND)

###################################################################################

# List header and source files for Server and Client
set(Server_HEADERS
    ../src/server/ZengineServer.h
    ../src/server/network/Network.h
    )

set (Server_SOURCES
    ../src/server/ZengineServer.cpp
    ../src/server/network/Network.cpp
    ../src/server/Main.cpp
    )

set(Client_HEADERS 
    ../src/client/ZengineClient.h
    ../src/client/network/Network.h
    ../src/client/renderer/shaders/Shader.h
    ../src/client/renderer/Renderer.h
    ../src/client/window/Window.h
    )

set(Client_SOURCES
    ../src/client/ZengineClient.cpp
    ../src/client/network/Network.cpp
    ../src/client/renderer/Renderer.cpp
    ../src/client/window/Window.cpp
    ../src/client/renderer/shaders/Shader.cpp
    ../src/client/Main.cpp
    )

set(Client_SHADERS
    ../src/client/renderer/shaders/simpleFragmentShader.fs 
    ../src/client/renderer/shaders/simpleVertexShader.vs 
    )



###################################################################################

# Add executables for Server and Client
add_executable(ZengineServer 
    ${Server_SOURCES} 
    ${Server_HEADERS} 
    ../src/server/Main.cpp 
    )
add_executable(ZengineClient 
    ${Client_SOURCES}
    ${Client_HEADERS} 
    ${Client_SHADERS}
    ../src/client/Main.cpp 
    )

# Add include directories for Server and Client
target_include_directories(ZengineServer PRIVATE 
    ${SDL2_NET_INCLUDE_DIR}
    ../src/server
    ../src/server/network
     )
target_include_directories(ZengineClient PRIVATE 
    ${OPENGL_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_NET_INCLUDE_DIR} 
    ../src/client
    ../src/client/network
    ../src/client/renderer
    ../src/client/renderer/shaders
    ../src/client/window
    )

# Install shader source files
INSTALL(
    FILES ${Client_SHADERS}
    DESTINATION ${CMAKE_BINARY_DIR}/../src/client/renderer/shaders
)

# Link Libraries for Server and Client
target_link_libraries (ZengineClient 
    ${SDL2_LIBRARY} 
    ${SDL2_NET_LIBRARY} 
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    )
target_link_libraries (ZengineServer 
    ${SDL2_NET_LIBRARY}
    )

###################################################################################