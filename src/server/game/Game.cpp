#include <Game.h>

bool Game::Initialize()
{
    std::string fileName = "../src/server/game/scripts/script.lua";

	luaState = luabridge::luaL_newstate();
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

    luabridge::LuaRef testString = getGlobal(luaState, "testString");
    luabridge::LuaRef testNum = getGlobal(luaState, "number");

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


    luabridge::LuaRef testTable = getGlobal(luaState, "gameWorld");
    luabridge::LuaRef testTitle = testTable["title"];
    luabridge::LuaRef testWidth = testTable["width"];
    luabridge::LuaRef testHeight = testTable["height"];
    luabridge::LuaRef testDepth = testTable["depth"];

    std::string titleString;
    if(testTitle.isString())
        titleString = testTitle.cast<std::string>();

    int width, height, depth;
    if( testWidth.isNil() || 
        testHeight.isNil() ||
        testDepth.isNil() )
    {
        printf("Variables not found!\n");
    }
    else
    {
        width = testWidth.cast<int>();
        height = testHeight.cast<int>();
        depth = testDepth.cast<int>();
    }

    printf("Title: %s \nwidth = %d \nheight = %d\ndepth = %d\n", titleString.c_str(), width, height, depth);
}

void Game::handleMessage(std::string message)
{
    /* Handle the message */

    /* Clear the message*/


    if(message == "create")
    {

        /* Create testEntity */
        Entity* testEntity = new Entity;

        /* Create graphics component */
        GraphicsComponent* testGraphicsComponent = new GraphicsComponent;
        testGraphicsComponent->setFileName("test.png");
        testEntity->addComponent(std::type_index(typeid(GraphicsComponent)), testGraphicsComponent);
        testGraphicsComponent->getFileName();

        /* Create Npc component */
        NpcComponent* testNpc = new NpcComponent;
        testNpc->setPhrase("I'm a test Npc!");
        testEntity->addComponent(std::type_index(typeid(NpcComponent)), testNpc);
        testNpc->getPhrase();


        message.clear();
    }

}

void Game::Update()
{
	
}

void Game::Close()
{

}