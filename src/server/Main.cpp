#include <ZengineServer.h> 



#include <LuaBridge.h>
#include <iostream>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}


using namespace luabridge;

/*
    Main   
*/
int main ( int argc, char* argv [] )
{
    ZengineServer TestServer;




	lua_State* L = luaL_newstate();
    luaL_dofile(L, "../src/server/scripts/script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;







    TestServer.Run();

  return 0;
}