#include <Game.h>

bool Game::Initialize()
{
    std::string fileName = "../src/server/game/scripts/script.lua";

	luaState = luaL_newstate();
    luaL_dofile(luaState, fileName.c_str());
    luaL_openlibs(luaState);
    lua_pcall(luaState, 0, 0, 0);

    if( luaL_loadfile(luaState, fileName.c_str()) ||
        lua_pcall(luaState, 0, 0, 0)
        )
    {
        printf("Script %s did not load properly!\n", fileName.c_str());
        return false;
    }

    LuaRef testString = getGlobal(luaState, "testString");
    LuaRef testNum = getGlobal(luaState, "number");

    std::string luaString;
    if(testString.isString())
        luaString = testString.cast<std::string>();
    else
    {
        printf("Variables not found!\n");
        return false;
    }

    int answer;
    if(!testNum.isNil())
        answer = testNum.cast<int>();
    else
    {
        printf("Variables not found!\n");
        return false;
    }

    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;


    LuaRef testTable = getGlobal(luaState, "gameWorld");
    LuaRef testTitle = testTable["title"];
    LuaRef testWidth = testTable["width"];
    LuaRef testHeight = testTable["height"];
    LuaRef testDepth = testTable["depth"];

    std::string titleString;
    if(testTitle.isString())
        titleString = testTitle.cast<std::string>();

    if(testWidth.isNil() ||)
}

void Game::Update()
{
	
}

void Game::Close()
{

}