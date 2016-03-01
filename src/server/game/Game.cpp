#include <Game.h>

bool Game::Initialize()
{
	luaState = luaL_newstate();
    luaL_dofile(luaState, "../src/server/game/scripts/script.lua");
    luaL_openlibs(luaState);
    lua_pcall(luaState, 0, 0, 0);

    LuaRef s = getGlobal(luaState, "testString");
    LuaRef n = getGlobal(luaState, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}

void Game::Update()
{
	
}

void Game::Close()
{

}