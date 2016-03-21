# Project-wide CMake for Zengine
# author: Chris Zehr, chris.zzehr@gmail.com

cmake_minimum_required (VERSION 2.8)
project (Zengine)

# Set output of final executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x") 
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11") 
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

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

#Find include directories for Lua5.3
find_package(Lua53 REQUIRED)
if(LUA53_FOUND)
    MESSAGE("Lua Correctly Found")
else(LUA53_FOUND)
    MESSAGE("Lua Environment missing")
endif(LUA53_FOUND)

###################################################################################

# List header and source files for Server and Client
set(Server_HEADERS
    ../src/server/ZengineServer.h
    ../src/server/utilities/LuaHelperFunctions.h
   # ../src/server/utilities/EcsHelperFunctions.h
    ../src/server/network/Network.h
    ../src/server/game/Game.h
    ../src/server/game/ecs/Entity.h
    ../src/server/game/ecs/Component.h
    ../src/server/game/ecs/System.h
    ../src/server/game/components/GraphicsComponent.h
    ../src/server/game/components/NpcComponent.h
    )
file(GLOB Server_HEADERS ../src/server/LuaBridge *.h)
file(GLOB Server_HEADERS ../src/server/LuaBridge/detail *.h)

set (Server_SOURCES
    ../src/server/ZengineServer.cpp
    ../src/server/utilities/LuaHelperFunctions.cpp
   # ../src/server/utilities/EcsHelperFunctions.cpp
    ../src/server/network/Network.cpp
    ../src/server/game/Game.cpp
    ../src/server/game/ecs/Entity.cpp
    ../src/server/game/ecs/Component.cpp
    ../src/server/game/ecs/System.cpp
    ../src/server/game/components/GraphicsComponent.cpp
    ../src/server/game/components/NpcComponent.cpp
    ../src/server/Main.cpp
    )

set(Client_HEADERS
    ../src/client/ZengineClient.h
    ../src/client/network/Network.h
    ../src/client/renderer/Renderer.h
    ../src/client/renderer/shaders/Shader.h
    ../src/client/window/Window.h
    )

set(Client_SOURCES
    ../src/client/ZengineClient.cpp
    ../src/client/network/Network.cpp
    ../src/client/renderer/Renderer.cpp
    ../src/client/renderer/shaders/Shader.cpp
    ../src/client/window/Window.cpp
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
    ${LUA53_INCLUDE_DIR}
    ../src/server
    ../src/server/utilities
    ../src/server/network
    ../src/server/game
    ../src/server/LuaBridge
    ../src/server/LuaBridge/detail
    ../src/server/game/ecs
    ../src/server/game/components
    ../src/server/game/systems
    )
target_include_directories(ZengineClient PRIVATE 
    ${OPENGL_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_NET_INCLUDE_DIR} 
    ${LUA53_INCLUDE_DIR}
    ../src/client
    ../src/client/network
    ../src/client/renderer
    ../src/client/renderer/shaders
    ../src/client/window
    )

# Install shader source files
INSTALL(
    FILES ${Client_SHADERS}
    DESTINATION ../src/client/renderer/shaders
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
    ${LUA53_LIBRARIES}
    ${CMAKE_DL_LIBS}
    )

###################################################################################